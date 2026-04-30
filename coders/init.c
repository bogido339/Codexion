/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:50:25 by username          #+#    #+#             */
/*   Updated: 2026/04/28 17:57:02 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_config	*init_config(char **argv)
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->number_of_coders = atoi(argv[1]);
	config->time_to_burnout = atoi(argv[2]);
	config->time_to_compile = atoi(argv[3]);
	config->time_to_debug = atoi(argv[4]);
	config->time_to_refactor = atoi(argv[5]);
	config->number_of_compiles_required = atoi(argv[6]);
	config->dongle_cooldown = atoi(argv[7]);
	config->scheduler = argv[8];
	config->stop_simulation = 0;
	config->start_time = get_time_ms();
	pthread_mutex_init(&config->stop_simulation_mutex, NULL);
	pthread_mutex_init(&config->print_mutex, NULL);
	pthread_mutex_init(&config->heap_push_mutex, NULL);
	return (config);
}

void	cleanup_dongles(t_dongle *dongles, int count)
{
	while (--count >= 0)
	{
		free(dongles[count].heap);
		pthread_mutex_destroy(&dongles[count].availability_mutex);
		pthread_mutex_destroy(&dongles[count].heap_mutex);
	}
	free(dongles);
}

int	init_one_dongle(t_dongle *d)
{
	d->is_available = 1;
	d->last_released = 0;
	pthread_mutex_init(&d->availability_mutex, NULL);
	pthread_mutex_init(&d->heap_mutex, NULL);
	d->heap = malloc(sizeof(t_coder *) * 2);
	if (!d->heap)
		return (0);
	d->heap[0] = NULL;
	d->heap[1] = NULL;
	return (1);
}

t_dongle	*init_dongles(t_config *config)
{
	int			i;
	int			total;
	t_dongle	*dongles;

	total = config->number_of_coders;
	dongles = malloc(sizeof(t_dongle) * total);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < total)
	{
		if (!init_one_dongle(&dongles[i]))
		{
			cleanup_dongles(dongles, i);
			return (NULL);
		}
		i++;
	}
	config->dongles = dongles;
	return (dongles);
}

t_coder	*init_coders(t_config *config)
{
	int		num_coders;
	int		i;
	t_coder	*coders;

	num_coders = config->number_of_coders;
	i = 0;
	coders = malloc(sizeof(t_coder) * num_coders);
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
		pthread_mutex_init(&coders[i].compile_mutex, NULL);
		i++;
	}
	config->coders = coders;
	return (coders);
}
