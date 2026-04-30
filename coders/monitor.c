/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 07:49:01 by username          #+#    #+#             */
/*   Updated: 2026/04/28 12:20:02 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_coders(t_config *config)
{
	int	i;
	int	finished_coders;

	i = 0;
	finished_coders = 0;
	while (i < config->number_of_coders)
	{
		if (get_compile_count(&config->coders[i])
			< config->number_of_compiles_required)
		{
			if (get_compile_time(&config->coders[i]) > config->time_to_burnout)
				return (stop_simulation(config),
					pthread_mutex_lock(&config->print_mutex),
					printf("%lld %d %s\n", get_time_ms() - config->start_time,
						config->coders[i].id, "burned out"),
					pthread_mutex_unlock(&config->print_mutex), 0);
		}
		else
			finished_coders++;
		i++;
	}
	if (finished_coders >= config->number_of_coders)
		return (0);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_config	*config;

	config = (t_config *)arg;
	while (check_coders(config))
		usleep(500);
	return (NULL);
}
