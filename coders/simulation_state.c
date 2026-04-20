/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:24:13 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/19 18:56:28 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int simulation_stopped(t_config *config)
{
    int stop;

    pthread_mutex_lock(&config->stop_simulation_mutex);
    stop = config->stop_simulation;
    pthread_mutex_unlock(&config->stop_simulation_mutex);
    return stop;
}

void stop_simulation(t_config *config)
{
    pthread_mutex_lock(&config->stop_simulation_mutex);
    config->stop_simulation = 1;
    pthread_mutex_unlock(&config->stop_simulation_mutex);
}
