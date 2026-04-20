/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:24:13 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/20 08:00:58 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long get_time_ms(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_status(t_coder *coder, char *msg, int count)
{
    int time_use;
    int coder_id;
    int i;

    if (simulation_stopped(coder->config))
        return;

    pthread_mutex_lock(&coder->config->print_mutex);
    time_use = get_time_ms() - coder->config->start_time;
    coder_id = coder->id;
    
    i = 0;
    while (i < count)
    {
        printf("%d %d %s\n", time_use, coder_id, msg);
        i++;
    }
    pthread_mutex_unlock(&coder->config->print_mutex);
}

void smart_sleep(long time, t_coder *coder)
{
    long long start_time;;

    start_time = get_time_ms();
    while (get_time_ms() - start_time < time)
    {
        if (simulation_stopped(coder->config))
            break;
        usleep(500);
    }
}


