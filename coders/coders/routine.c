/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/20 08:13:31 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int take_dongles(t_coder *coder)
{
    if (coder->first_push)
    {
        pthread_mutex_lock(&coder->config->heap_push_mutex);
        enqueue_first_time(coder);
        pthread_mutex_unlock(&coder->config->heap_push_mutex);
    }
    else
    {
        pthread_mutex_lock(&coder->config->heap_push_mutex);
        add_coder_to_heap(coder);
        pthread_mutex_unlock(&coder->config->heap_push_mutex);
    }
    
    while (1)
    {
        if (are_dongles_ready(coder) && has_scheduler_turn(coder))
            return (lock_dongles(coder), print_status(coder, "has taken a dongle", 2), 1);
        if (simulation_stopped(coder->config))
            return (0);
        usleep(100);
    }
    return (1);
}

void handle_single_coder(t_coder *coder)
{
    print_status(coder, "has taken a dongle", 1);
    smart_sleep(coder->config->time_to_compile, coder);    
}

void *coder_routine(void *arg)
{
    
    t_coder *coder;

    coder = (t_coder *)arg;

    if (coder->config->number_of_coders == 1)
        return (handle_single_coder(coder), NULL);

    while (1)
    {
        if (simulation_stopped(coder->config))
            break;
        if (!take_dongles(coder))
            break;
        compile(coder);
        release_dongles(coder);
        debug(coder);
        refactor(coder);
    }
    return (NULL);

}
