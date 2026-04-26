/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:50:25 by username          #+#    #+#             */
/*   Updated: 2026/04/26 11:00:31 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_config	*init_config(char **argv)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	config->number_of_coders = atoi(argv[1]);
	config->time_to_burnout = atoi(argv[2]);
	config->time_to_compile = atoi(argv[3]);
	config->time_to_debug = atoi(argv[4]);
	config->time_to_refactor = atoi(argv[5]);
	config->number_of_compiles_required = atoi(argv[6]);
	config->dongle_cooldown = atoi(argv[7]);
	config->scheduler = argv[8];
	config->stop_simulation = 0;
	config->all_ready = 0;
	config->start_time = get_time_ms();
	pthread_mutex_init(&config->stop_simulation_mutex, NULL);
	pthread_mutex_init(&config->print_mutex, NULL);
	pthread_mutex_init(&config->heap_push_mutex, NULL);
	pthread_mutex_init(&config->all_ready_mutex, NULL);
	return (config);
}

t_dongle	*init_dongles(t_config *config)
{
	int			num_dongles = config->number_of_coders;
	int			i = 0;
	t_dongle	*dongles = malloc(sizeof(t_dongle) *num_dongles);

	while (i < num_dongles)
	{
		dongles[i].is_available = 1;
		dongles[i].last_released = 0;
		pthread_mutex_init(&dongles[i].availability_mutex, NULL);
		pthread_mutex_init(&dongles[i].heap_mutex, NULL);
		dongles[i].heap = malloc(sizeof(t_coder *) * 2);
		dongles[i].heap[0] = NULL;
		dongles[i].heap[1] = NULL;
		i++;
	}
	config->dongles = dongles;
	return (dongles);
}

t_coder	*init_coders(t_config *config)
{
	int		num_coders = config->number_of_coders;
	int		i = 0;
	t_coder	*coders = malloc(sizeof(t_coder) *num_coders);

	if (!coders)
		return (NULL);
	while (i < num_coders)
	{
		coders[i].id = i + 1;
		coders[i].last_compile_time = get_time_ms();
		coders[i].compile_count = 0;
		coders[i].left_dongle = &config->dongles[i];
		coders[i].right_dongle = &config->dongles[(i + 1) % num_coders];
		coders[i].config = config;
		coders[i].first_push = 1;
		i++;
	}
	config->coders = coders;
	return (coders);
}
