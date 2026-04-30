/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:52:37 by username          #+#    #+#             */
/*   Updated: 2026/04/28 11:43:30 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	lock_availability_safe(t_coder *coder)
{
	pthread_mutex_t	*first_lock;
	pthread_mutex_t	*second_lock;

	if (&coder->left_dongle->availability_mutex
		< &coder->right_dongle->availability_mutex)
	{
		first_lock = &coder->left_dongle->availability_mutex;
		second_lock = &coder->right_dongle->availability_mutex;
	}
	else
	{
		first_lock = &coder->right_dongle->availability_mutex;
		second_lock = &coder->left_dongle->availability_mutex;
	}
	pthread_mutex_lock(first_lock);
	pthread_mutex_lock(second_lock);
}

void	unlock_availability_safe(t_coder *coder)
{
	pthread_mutex_t	*first_lock;
	pthread_mutex_t	*second_lock;

	if (&coder->left_dongle->availability_mutex
		< &coder->right_dongle->availability_mutex)
	{
		first_lock = &coder->left_dongle->availability_mutex;
		second_lock = &coder->right_dongle->availability_mutex;
	}
	else
	{
		first_lock = &coder->right_dongle->availability_mutex;
		second_lock = &coder->left_dongle->availability_mutex;
	}
	pthread_mutex_unlock(second_lock);
	pthread_mutex_unlock(first_lock);
}

int	try_take_dongles(t_coder *coder)
{
	int	ready;

	if (!has_scheduler_turn(coder))
		return (0);
	lock_availability_safe(coder);
	ready = 1;
	if (!coder->left_dongle->is_available
		|| (get_time_ms() - coder->left_dongle->last_released)
		<= coder->config->dongle_cooldown)
		ready = 0;
	if (!coder->right_dongle->is_available
		|| (get_time_ms() - coder->right_dongle->last_released)
		<= coder->config->dongle_cooldown)
		ready = 0;
	if (ready)
	{
		coder->left_dongle->is_available = 0;
		coder->right_dongle->is_available = 0;
		unlock_availability_safe(coder);
		return (1);
	}
	unlock_availability_safe(coder);
	return (0);
}

void	release_dongles(t_coder *coder)
{
	dequeue_from_heap(coder);
	pthread_mutex_lock(&coder->left_dongle->availability_mutex);
	coder->left_dongle->is_available = 1;
	coder->left_dongle->last_released = get_time_ms();
	pthread_mutex_unlock(&coder->left_dongle->availability_mutex);
	pthread_mutex_lock(&coder->right_dongle->availability_mutex);
	coder->right_dongle->is_available = 1;
	coder->right_dongle->last_released = get_time_ms();
	pthread_mutex_unlock(&coder->right_dongle->availability_mutex);
}
