/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by username          #+#    #+#             */
/*   Updated: 2026/04/26 10:57:53 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	schedule_fifo(t_coder *coder)
{
	if (coder != coder->left_dongle->heap[0]
		|| coder != coder->right_dongle->heap[0])
		return (0);
	else
		return (1);
}

int	schedule_edf(t_coder *coder)
{
	if (coder->left_dongle->heap[1] == coder)
		sort_dongle_heap(coder->left_dongle);
	if (coder->right_dongle->heap[1] == coder)
		sort_dongle_heap(coder->right_dongle);
	return (coder == coder->left_dongle->heap[0]
		&& coder == coder->right_dongle->heap[0]);
}

int	has_scheduler_turn(t_coder *coder)
{
	int	result;

	result = 0;
	if (!strcmp(coder->config->scheduler, "edf"))
	{
		lock_dongles_safe(coder);
		result = schedule_edf(coder);
		unlock_dongles_safe(coder);
		return (result);
	}
	if (!strcmp(coder->config->scheduler, "fifo"))
	{
		lock_dongles_safe(coder);
		result = schedule_fifo(coder);
		unlock_dongles_safe(coder);
		return (result);
	}
	return (result);
}
