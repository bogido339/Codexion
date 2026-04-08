/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 07:49:01 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/08 14:37:06 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int check_coder(t_config *config)
{
    int i = 0;
    int num_coder = config->number_of_coders;
    
    while (i < num_coder)
    {
        if (get_time_ms() - config->coders[i].last_compile_time > config->time_to_burnout)
        {
            pthread_mutex_lock(&config->burned_out_mutex);
            config->burned_out = 1;
            pthread_mutex_unlock(&config->print_mutex);
            
            pthread_mutex_lock(&config->burned_out_mutex);
            print_status(config->coders[i], "burned out");
            pthread_mutex_unlock(&config->print_mutex);
            return 1;
        }   
    }
    return 0;
}
void *monitor_routine(void *arg)
{
    t_config *config;

    config = (t_config *)arg;
    while (!check_coders(config))
        usleep(500);
    return NULL;
}

int start_monitor(t_config *config)
{
    create_thread(&config->monitor, NULL, monitor_routine, config);
    pthread_join(config->monitor, NULL);

    return (0);
}