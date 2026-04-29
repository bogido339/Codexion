/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by username          #+#    #+#             */
/*   Updated: 2026/04/28 11:32:55 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	assign_heap(t_coder *coder, int left, int right)
{
	coder->left_dongle->heap[left] = coder;
	coder->right_dongle->heap[right] = coder;
}

void	enqueue_first_time(t_coder *coder)
{
	lock_dongles_safe(coder);
	if (coder->id % 2 && !coder->left_dongle->heap[0]
		&& !coder->right_dongle->heap[0])
		assign_heap(coder, 0, 0);
	else if (!(coder->id % 2) && !coder->left_dongle->heap[1]
		&& !coder->right_dongle->heap[1])
		assign_heap(coder, 1, 1);
	else if (!coder->left_dongle->heap[1]
		&& coder->right_dongle->heap[1])
		assign_heap(coder, 1, 0);
	else
		assign_heap(coder, 0, 1);
	if (coder->first_push)
		coder->first_push = 0;
	unlock_dongles_safe(coder);
}

void	dequeue_from_heap(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->heap_mutex);
	coder->left_dongle->heap[0] = coder->left_dongle->heap[1];
	coder->left_dongle->heap[1] = NULL;
	pthread_mutex_unlock(&coder->left_dongle->heap_mutex);
	pthread_mutex_lock(&coder->right_dongle->heap_mutex);
	coder->right_dongle->heap[0] = coder->right_dongle->heap[1];
	coder->right_dongle->heap[1] = NULL;
	pthread_mutex_unlock(&coder->right_dongle->heap_mutex);
}

void	swap_coders(t_coder **heap)
{
	t_coder	*coder;

	coder = heap[0];
	heap[0] = heap[1];
	heap[1] = coder;
}

void	sort_dongle_heap(t_dongle *dongle)
{
	t_coder	*c0;
	t_coder	*c1;

	if (!dongle->heap[0] || !dongle->heap[1])
		return ;
	c0 = dongle->heap[0];
	c1 = dongle->heap[1];
	if (get_compile_time(c0) > get_compile_time(c1))
		swap_coders(dongle->heap);
	else if (get_compile_time(c0) == get_compile_time(c1)
		&& get_compile_count(c0) < get_compile_count(c1))
		swap_coders(dongle->heap);
}
