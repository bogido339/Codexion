/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 17:52:37 by username          #+#    #+#             */
/*   Updated: 2026/04/26 11:00:43 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	are_dongles_ready(t_coder *coder)
{
	int	ready;

	ready = 1;
	pthread_mutex_lock(&coder->left_dongle->availability_mutex);
	ready *= coder->left_dongle->is_available;
	ready *= (get_time_ms() - coder->left_dongle->last_released) > coder->config->dongle_cooldown;
	pthread_mutex_unlock(&coder->left_dongle->availability_mutex);
	pthread_mutex_lock(&coder->right_dongle->availability_mutex);
	ready *= coder->right_dongle->is_available;
	ready *= (get_time_ms() - coder->right_dongle->last_released) > coder->config->dongle_cooldown;
	pthread_mutex_unlock(&coder->right_dongle->availability_mutex);
	return (ready);
}

void	lock_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->availability_mutex);
	coder->left_dongle->is_available = 0;
	pthread_mutex_unlock(&coder->left_dongle->availability_mutex);
	pthread_mutex_lock(&coder->right_dongle->availability_mutex);
	coder->right_dongle->is_available = 0;
	pthread_mutex_unlock(&coder->right_dongle->availability_mutex);
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
