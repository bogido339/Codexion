/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/20 07:59:25 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int schedule_fifo(t_coder *coder)
{
    if (coder != coder->left_dongle->heap[0] || coder != coder->right_dongle->heap[0])
        return (0);
    else
        return (1);
}

int schedule_edf(t_coder *coder)
{
    if (coder->left_dongle->heap[1] == coder)
        sort_dongle_heap(coder->left_dongle);
    if (coder->right_dongle->heap[1] == coder)
        sort_dongle_heap(coder->right_dongle);

    if (coder == coder->left_dongle->heap[0] && coder == coder->right_dongle->heap[0])
        return (1);
    return (0);
}

int has_scheduler_turn(t_coder *coder)
{
    int result;

    result = 0;
    if (strcmp(coder->config->scheduler, "edf") == 0)
    {
        pthread_mutex_lock(&coder->left_dongle->heap_mutex);
        result = schedule_edf(coder);
        pthread_mutex_unlock(&coder->left_dongle->heap_mutex);
        return result;
    }
    if (strcmp(coder->config->scheduler, "fifo") == 0)
    {
        pthread_mutex_lock(&coder->left_dongle->heap_mutex);
        result = schedule_fifo(coder);
        pthread_mutex_unlock(&coder->left_dongle->heap_mutex);
        return result;
    }
    return (result);
}

