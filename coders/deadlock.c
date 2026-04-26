/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:03:27 by username          #+#    #+#             */
/*   Updated: 2026/04/26 10:56:15 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	lock_dongles_safe(t_coder *coder)
{
	pthread_mutex_t	*first_lock;
	pthread_mutex_t	*second_lock;

	if (&coder->left_dongle->heap_mutex < &coder->right_dongle->heap_mutex)
	{
		first_lock = &coder->left_dongle->heap_mutex;
		second_lock = &coder->right_dongle->heap_mutex;
	}
	else
	{
		first_lock = &coder->right_dongle->heap_mutex;
		second_lock = &coder->left_dongle->heap_mutex;
	}
	pthread_mutex_lock(first_lock);
	pthread_mutex_lock(second_lock);
}

void	unlock_dongles_safe(t_coder *coder)
{
	pthread_mutex_t	*first_lock;
	pthread_mutex_t	*second_lock;

	if (&coder->left_dongle->heap_mutex < &coder->right_dongle->heap_mutex)
	{
		first_lock = &coder->left_dongle->heap_mutex;
		second_lock = &coder->right_dongle->heap_mutex;
	}
	else
	{
		first_lock = &coder->right_dongle->heap_mutex;
		second_lock = &coder->left_dongle->heap_mutex;
	}
	pthread_mutex_unlock(second_lock);
	pthread_mutex_unlock(first_lock);
}
