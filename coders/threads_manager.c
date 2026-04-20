/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:59 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/19 18:54:27 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void start_threads(t_config *config)
{
    int i;
    int n;

    n = config->number_of_coders;
    i = 0;
    while(i < n)
    {
        pthread_create(&config->coders[i].coder_thread_id, NULL, coder_routine, &config->coders[i]);
        i++;
    }

    pthread_create(&config->monitor_id, NULL, monitor_routine, config);

    i = 0;
    while (i < n)
    {
        pthread_join(config->coders[i].coder_thread_id, NULL);
        i++;
    }
    pthread_join(config->monitor_id, NULL);
    
}
