/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:24:13 by username          #+#    #+#             */
/*   Updated: 2026/04/28 19:00:27 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	simulation_stopped(t_config *config)
{
	int	stop;

	pthread_mutex_lock(&config->stop_simulation_mutex);
	stop = config->stop_simulation;
	pthread_mutex_unlock(&config->stop_simulation_mutex);
	return (stop);
}

void	stop_simulation(t_config *config)
{
	pthread_mutex_lock(&config->stop_simulation_mutex);
	config->stop_simulation = 1;
	pthread_mutex_unlock(&config->stop_simulation_mutex);
}

void	wait_all_threads_ready(t_config *config)
{
	while (1)
	{
		pthread_mutex_lock(&config->ready_mutex);
		if (config->ready == 1)
		{
			pthread_mutex_unlock(&config->ready_mutex);
			break ;
		}
		pthread_mutex_unlock(&config->ready_mutex);
		usleep(50);
	}
}
