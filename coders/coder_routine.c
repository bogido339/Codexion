/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/12 11:16:51 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int take_dongles(t_coder *coder)
{
    long long current_time;
    int left_dg;
    int right_df;
    pthread_mutex_lock(&coder->config->add_in_heap);
    add_coder_in_last_the_heep(coder);
    pthread_mutex_unlock(&coder->config->add_in_heap);
    while (1)
    {
        if (simulation_stopped(coder->config))
            return (1);
        current_time = get_time_ms();
        if (coder->left_dongle->is_available &&
            (current_time - coder->left_dongle->last_released >= coder->config->dongle_cooldown)) {
            left_dg = 1;
        } else {
            left_dg = 0;
        }
        
        if (coder->right_dongle->is_available &&
            (current_time - coder->right_dongle->last_released >= coder->config->dongle_cooldown)) {
            right_df = 1;
        } else {
            right_df = 0;
        }
        int is_first = is_first_coder_in_heep(coder);

        if (left_dg && right_df && is_first)
        {
            pop_in_start_the_heep(coder);
            break;
        }
            
    }
    return 0;
    // pthread_mutex_lock(&coder->config->print_mutex);
    
    pthread_mutex_lock(&coder->right_dongle->mutex);
    print_status(coder, "has taken a dongle");
    coder->right_dongle->is_available = 0;
    coder->last_compile_time = get_time_ms();
    pthread_mutex_unlock(&coder->right_dongle->mutex);

    pthread_mutex_lock(&coder->left_dongle->mutex);
    print_status(coder, "has taken a dongle");
    coder->left_dongle->is_available = 0;
    coder->last_compile_time = get_time_ms();
    pthread_mutex_unlock(&coder->left_dongle->mutex);

    // pthread_mutex_unlock(&coder->config->print_mutex);

}


void release_dongles(t_coder *coder)
{
    pthread_mutex_lock(&coder->right_dongle->mutex);
    coder->right_dongle->is_available = 1;
    coder->right_dongle->last_released = get_time_ms();
    pthread_mutex_unlock(&coder->right_dongle->mutex);

    pthread_mutex_lock(&coder->left_dongle->mutex);
    coder->left_dongle->is_available = 1;
    coder->left_dongle->last_released = get_time_ms();
    pthread_mutex_unlock(&coder->left_dongle->mutex);

}

void *handle_single_coder(t_coder *coder)
{
    print_status(coder, "has taken a dongle");
    usleep(coder->config->time_to_compile * 1000);    
    return NULL;
}

void *coder_routine(void *arg)
{
    
    t_coder *coder = (t_coder *)arg;
    
    while (1)
    {
        if (coder->config->number_of_coders == 1)
            return (handle_single_coder(coder));
        if (coder->compile_count >= coder->config->number_of_compiles_required)
            break;
        if (simulation_stopped(coder->config))
            break;
        
        if (take_dongles(coder))
            return NULL;
        compile(coder);
        release_dongles(coder);
        debug(coder);
        refactor(coder);
    }
    
    return (NULL);
}