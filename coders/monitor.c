/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 07:49:01 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/13 16:04:15 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int check_coder(t_config *config)
{
    int i = 0;
    int num_coder = config->number_of_coders;
    int compile_count;
    long long last_time;
    int finished_coders = 0;
    
    while (i < num_coder)
    {
        pthread_mutex_lock(&config->monitor_mutex);
        compile_count = config->coders[i].compile_count;
        last_time = config->coders[i].last_compile_time;
        pthread_mutex_unlock(&config->monitor_mutex);

        if (compile_count < config->number_of_compiles_required)
        {
            if (get_time_ms() - last_time > config->time_to_burnout)
            {
                pthread_mutex_lock(&config->stop_mutex);
                config->stop = 1;
                pthread_mutex_unlock(&config->stop_mutex);

                print_status(&config->coders[i], "burned out", 1);
                
                return 0;
            }
        }
        else
            finished_coders++;
        i++;
    }
    
    if (finished_coders == num_coder)
    {
        pthread_mutex_lock(&config->stop_mutex);
        config->stop = 1;
        pthread_mutex_unlock(&config->stop_mutex);
        return 0;
    }
    
    return 1;
}

void *monitor_routine(void *arg)
{
    t_config *config;

    config = (t_config *)arg;
    while (check_coder(config))
        usleep(500);

    return NULL;
}

int start_monitor(t_config *config)
{
    pthread_create(&config->monitor, NULL, monitor_routine, config);
    return (0);
}