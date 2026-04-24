/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:51:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/24 18:03:32 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int schedule_fifo(t_coder *coder)
{
    if (coder != get_heap(coder->left_dongle, 0) || coder != get_heap(coder->right_dongle, 0))
        return (0);
    else
        return (1);
}

int schedule_edf(t_coder *coder)
{
    if (get_heap(coder->left_dongle, 1) == coder)
        sort_dongle_heap(coder->left_dongle);
    if (get_heap(coder->right_dongle, 1) == coder)
        sort_dongle_heap(coder->right_dongle);

    if (coder == get_heap(coder->left_dongle, 0)
    && coder == get_heap(coder->right_dongle, 0))
        return (1);
    return (0);
}

int has_scheduler_turn(t_coder *coder)
{
    if (strcmp(coder->config->scheduler, "edf") == 0)
        return schedule_edf(coder);
    else
        return schedule_fifo(coder);
}

