/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   routine.c                                         :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/03/30 16:51:50 by username         #+#    #+#              */
/*   Updated: 2026/04/26 16:49:06 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	take_dongles(t_coder *coder)
{
	if (coder->first_push)
	{
		pthread_mutex_lock(&coder->config->heap_push_mutex);
		enqueue_first_time(coder);
		pthread_mutex_unlock(&coder->config->heap_push_mutex);
	}
	else
	{
		pthread_mutex_lock(&coder->config->heap_push_mutex);
		add_coder_to_heap(coder);
		pthread_mutex_unlock(&coder->config->heap_push_mutex);
	}
	while (1)
	{
		if (simulation_stopped(coder->config))
			return (0);
		int a = has_scheduler_turn(coder);
		if (are_dongles_ready(coder) && a)
			return (lock_dongles(coder), print_status(coder, "has taken a dongle", 2), 1);
		usleep(1000);
	}
	return (1);
}

void	handle_single_coder(t_coder *coder)
{
	print_status(coder, "has taken a dongle", 1);
	smart_sleep(coder->config->time_to_compile, coder);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *) arg;
	if (coder->config->number_of_coders == 1)
		return (handle_single_coder(coder), NULL);
	while (!get_all_ready(coder->config))
        usleep(100);
	while (1)
	{
		if (simulation_stopped(coder->config))
			break ;
		if (!take_dongles(coder))
			break ;
		compile(coder);
		release_dongles(coder);
		debug(coder);
		refactor(coder);
		if (get_compile_count(coder) >= coder->config->number_of_compiles_required)
			break ;
	}
	return (NULL);
}
