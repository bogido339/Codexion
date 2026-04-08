/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/08 14:49:44 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



void take_dongles(t_coder *coder)
{
    long long current_time;
    int left_dg;
    int right_df;

    while (1)
    {
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

        if (left_dg && right_df)
            break;
        
    }
    pthread_mutex_lock(&coder->config->dongles->mutex);
    print_status(coder, "has taken a dongle");
    print_status(coder, "has taken a dongle");
    
    coder->left_dongle->is_available = 0;
    coder->right_dongle->is_available = 0;

    coder->last_compile_time = get_time_ms();

    pthread_mutex_unlock(&coder->config->dongles->mutex);
}


void release_dongles(t_coder *coder, pthread_cond_t *cond, pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
    coder->left_dongle->is_available = 1;
    coder->right_dongle->is_available = 1;
    coder->left_dongle->last_released = get_time_ms();
    coder->right_dongle->last_released = get_time_ms();
    pthread_cond_broadcast(cond);
    pthread_mutex_unlock(mutex);
}

void *coder_routine(void *arg)
{
    
    t_coder *coder = (t_coder *)arg;
    
    while (1)
    {
        take_dongles(coder);
        comple(coder);
        release_dongles(coder);
        debug(coder);
        refactor(coder);   
    }
    
    return (NULL);
}