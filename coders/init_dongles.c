/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:50:25 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/13 14:52:18 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_dongle    *init_dongles(t_config *config)
{
    int num_dongles = config->number_of_coders;
    int i = 0;
    
    t_dongle *dongles = malloc(sizeof(t_dongle) * num_dongles);

    while (i < num_dongles)
    {
        pthread_mutex_init(&dongles[i].available_mutex, NULL);
        pthread_mutex_init(&dongles[i].released_mutex, NULL);
        
        dongles[i].is_available = 1;
        dongles[i].last_released = 0;

        dongles[i].heap = malloc(sizeof(t_coder) * 2);
        dongles[i].heap[0] = NULL;
        dongles[i].heap[1] = NULL;
        i++;
    }
    config->dongles = dongles;
    return dongles;
}