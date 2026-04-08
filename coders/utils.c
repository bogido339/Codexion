/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:24:13 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/08 13:35:25 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long get_time_ms(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_status(t_coder *coder, char *msg)
{
    int time_use;
    int coder_id;

    time_use = get_time_ms() - coder->config->start_time;
    coder_id = coder->id;

    printf("%d %d %s\n", time_use, coder_id, msg);
}

int simulation_stopped(t_config *config)
{
    int result;
    pthread_mutex_lock(&config->burned_out_mutex);
    if (config->burned_out)
        result = 1;
    else
        result = 0;
    pthread_mutex_unlock(&config->burned_out_mutex);
    return result;

}

void smart_sleep(long time, t_config *config)
{
    long start_time = get_time_ms();
    while (get_time_ms() - start_time < time)
    {
        if (simulation_stopped(config))
            break;
        usleep(500);
    }
}


