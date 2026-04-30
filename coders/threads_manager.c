/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:59 by username          #+#    #+#             */
/*   Updated: 2026/04/28 11:07:15 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	sync_start_time(t_config *config)
{
	int	i;

	pthread_mutex_lock(&config->ready_mutex);
	config->start_time = get_time_ms();
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_mutex_lock(&config->coders[i].compile_mutex);
		config->coders[i].last_compile_time = config->start_time;
		pthread_mutex_unlock(&config->coders[i].compile_mutex);
		i++;
	}
	config->ready = 1;
	pthread_mutex_unlock(&config->ready_mutex);
}

void	start_threads(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_create(&config->coders[i].coder_thread_id, NULL,
			coder_routine, &config->coders[i]);
		i++;
	}
	pthread_create(&config->monitor_id, NULL, monitor_routine, config);
	sync_start_time(config);
	i = 0;
	while (i < config->number_of_coders)
	{
		pthread_join(config->coders[i].coder_thread_id, NULL);
		i++;
	}
	pthread_join(config->monitor_id, NULL);
}
