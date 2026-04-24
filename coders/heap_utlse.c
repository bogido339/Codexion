/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utlse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:39:44 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/24 17:00:13 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder *get_heap(t_dongle *dongle, int adr)
{
    t_coder *coder;

    pthread_mutex_lock(&dongle->heap_mutex);
    coder = dongle->heap[adr];
    pthread_mutex_unlock(&dongle->heap_mutex);
    return coder;
}

void set_heap(t_dongle *dongle, t_coder *coder, int adr)
{
    pthread_mutex_lock(&dongle->heap_mutex);
    dongle->heap[adr] = coder;
    pthread_mutex_unlock(&dongle->heap_mutex);
}