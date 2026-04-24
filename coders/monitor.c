/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 07:49:01 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/24 14:44:43 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int check_coders(t_config *config)
{
    int i;
    int finished_coders;
    int time_use;

    i = 0;
    finished_coders = 0;
    while (i < config->number_of_coders)
    {
        if (get_compile_count(&config->coders[i]) < config->number_of_compiles_required)
        {
            if (get_compile_time(&config->coders[i]) > config->time_to_burnout)
            {
                stop_simulation(config);
                time_use = get_time_ms() - config->start_time;
                printf("%d %d %s\n", time_use, config->coders[i].id, "burned out");
                return (0);
            }
        }
        else
            finished_coders++;
        i++;
    }
    if (finished_coders == config->number_of_coders)
        return (stop_simulation(config), 0);
    return (1);
}

void *monitor_routine(void *arg)
{
    t_config *config;

    config = (t_config *)arg;

    while (check_coders(config))
        usleep(500);
        
    return NULL;
}
