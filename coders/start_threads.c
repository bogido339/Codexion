/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:08:59 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/12 10:38:18 by mbougajd         ###   ########.fr       */
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
        pthread_create(&config->coders[i].coder_thread, NULL, coder_routine, &config->coders[i]);
        i++;
    }
    start_monitor(config);
    i = 0;
    while (i < n)
    {
        pthread_join(config->coders[i].coder_thread, NULL);
        i++;
    }
    pthread_join(config->monitor, NULL);
    
}
