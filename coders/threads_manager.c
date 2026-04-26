/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:59 by username          #+#    #+#             */
/*   Updated: 2026/04/26 11:00:08 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int get_all_ready(t_config *config)
{
	int all_ready;

	pthread_mutex_lock(&config->all_ready_mutex);
	all_ready = config->all_ready;
	pthread_mutex_unlock(&config->all_ready_mutex);
	return (all_ready);

}

void set_all_ready(t_config *config)
{
	pthread_mutex_lock(&config->all_ready_mutex);
	config->all_ready = 1;
	pthread_mutex_unlock(&config->all_ready_mutex);
}

void	start_threads(t_config *config)
{
	int	i;
	int	n;

	n = config->number_of_coders;
	i = 0;
	while (i < n)
	{
		pthread_create(&config->coders[i].coder_thread_id, NULL, coder_routine, &config->coders[i]);
		i++;
	}
	pthread_create(&config->monitor_id, NULL, monitor_routine, config);
	set_all_ready(config);
	i = 0;
	while (i < n)
	{
		pthread_join(config->coders[i].coder_thread_id, NULL);
		i++;
	}
	pthread_join(config->monitor_id, NULL);
}
