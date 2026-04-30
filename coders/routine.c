/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by username          #+#    #+#             */
/*   Updated: 2026/04/28 11:28:44 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	add_coder_to_heap(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->heap_mutex);
	if (!coder->left_dongle->heap[0])
		coder->left_dongle->heap[0] = coder;
	else
		coder->left_dongle->heap[1] = coder;
	pthread_mutex_unlock(&coder->left_dongle->heap_mutex);
	pthread_mutex_lock(&coder->right_dongle->heap_mutex);
	if (!coder->right_dongle->heap[0])
		coder->right_dongle->heap[0] = coder;
	else
		coder->right_dongle->heap[1] = coder;
	pthread_mutex_unlock(&coder->right_dongle->heap_mutex);
}

int	take_dongles(t_coder *coder)
{
	while (1)
	{
		if (simulation_stopped(coder->config))
			return (0);
		if (try_take_dongles(coder))
		{
			print_status(coder, "has taken a dongle", 2);
			return (1);
		}
		usleep(100);
	}
	return (1);
}

void	handle_single_coder(t_coder *coder)
{
	print_status(coder, "has taken a dongle", 1);
	smart_sleep(coder->config->time_to_compile, coder);
}

void	run_simulation_loop(t_coder *coder)
{
	while (1)
	{
		if (simulation_stopped(coder->config) || !take_dongles(coder))
			break ;
		compile(coder);
		release_dongles(coder);
		debug(coder);
		refactor(coder);
		if (get_compile_count(coder)
			>= coder->config->number_of_compiles_required)
			break ;
		pthread_mutex_lock(&coder->config->heap_push_mutex);
		add_coder_to_heap(coder);
		pthread_mutex_unlock(&coder->config->heap_push_mutex);
	}
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	pthread_mutex_lock(&coder->config->heap_push_mutex);
	enqueue_first_time(coder);
	pthread_mutex_unlock(&coder->config->heap_push_mutex);
	wait_all_threads_ready(coder->config);
	if (coder->config->number_of_coders == 1)
	{
		handle_single_coder(coder);
		return (NULL);
	}
	run_simulation_loop(coder);
	return (NULL);
}
