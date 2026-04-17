/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/17 06:26:41 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int is_dongle_usable(t_coder *coder)
{
    long long current_time;
    int left_dg;
    int right_df;
    int is_first;

    current_time = get_time_ms();
    
    pthread_mutex_lock(&coder->left_dongle->available_mutex);
    pthread_mutex_lock(&coder->left_dongle->released_mutex);
    pthread_mutex_lock(&coder->right_dongle->available_mutex);
    pthread_mutex_lock(&coder->right_dongle->released_mutex);
    left_dg = (coder->left_dongle->is_available &&
        (current_time - coder->left_dongle->last_released >= coder->config->dongle_cooldown));
    right_df = (coder->right_dongle->is_available &&
        (current_time - coder->right_dongle->last_released >= coder->config->dongle_cooldown));
    pthread_mutex_unlock(&coder->left_dongle->available_mutex);
    pthread_mutex_unlock(&coder->left_dongle->released_mutex);
    pthread_mutex_unlock(&coder->right_dongle->available_mutex);
    pthread_mutex_unlock(&coder->right_dongle->released_mutex);

    is_first = is_first_coder_in_heep(coder);

    if (left_dg && right_df && is_first)
        return 1;
    return 0;
}

int take_dongles(t_coder *coder)
{
    add_coder_in_last_the_heep(coder);
    
    while (1)
    {
        if (simulation_stopped(coder))
            return 0;
        if (is_dongle_usable(coder))
        {
            pop_in_start_the_heep(coder);
            break;
        }
        usleep(100);
 
    }
    
    pthread_mutex_lock(&coder->right_dongle->available_mutex);
    coder->right_dongle->is_available = 0;
    pthread_mutex_unlock(&coder->right_dongle->available_mutex);
    
    pthread_mutex_lock(&coder->config->monitor_mutex);
    coder->last_compile_time = get_time_ms();
    pthread_mutex_unlock(&coder->config->monitor_mutex);

    pthread_mutex_lock(&coder->left_dongle->available_mutex);
    coder->left_dongle->is_available = 0;
    pthread_mutex_unlock(&coder->left_dongle->available_mutex);
    
    print_status(coder, "has taken a dongle", 2);

    return 1;

}


void release_dongles(t_coder *coder)
{
    pthread_mutex_lock(&coder->right_dongle->available_mutex);
    coder->right_dongle->is_available = 1;
    pthread_mutex_unlock(&coder->right_dongle->available_mutex);
    
    pthread_mutex_lock(&coder->right_dongle->released_mutex);
    coder->right_dongle->last_released = get_time_ms();
    pthread_mutex_unlock(&coder->right_dongle->released_mutex);

    pthread_mutex_lock(&coder->left_dongle->available_mutex);
    coder->left_dongle->is_available = 1;
    pthread_mutex_unlock(&coder->left_dongle->available_mutex);
    
    pthread_mutex_lock(&coder->left_dongle->released_mutex);
    coder->left_dongle->last_released = get_time_ms();
    pthread_mutex_unlock(&coder->left_dongle->released_mutex);

}

void *handle_single_coder(t_coder *coder)
{
    print_status(coder, "has taken a dongle", 1);
    usleep(coder->config->time_to_compile * 1000);    
    return NULL;
}

void *coder_routine(void *arg)
{
    t_coder *coder;

    coder = (t_coder *)arg;
    while (1)
    {
        if (coder->config->number_of_coders == 1)
            return (handle_single_coder(coder));

        if (simulation_stopped(coder))
            break;

        if (!take_dongles(coder))
            break;
        compile(coder);
        release_dongles(coder);
        debug(coder);
        refactor(coder);
        printf("not");
    }
    return (NULL);
}
