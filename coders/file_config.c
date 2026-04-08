/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 13:20:57 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/08 12:11:59 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_config *fill_config(char **argv)
{
    t_config *config;
    config = malloc(sizeof(t_config));

    config->number_of_coders = atoi(argv[1]);
   
    config->time_to_burnout = atoi(argv[2]);
    config->time_to_compile = atoi(argv[3]);
    config->time_to_debug = atoi(argv[4]);
    config->time_to_refactor = atoi(argv[5]);
    config->number_of_compiles_required = atoi(argv[6]);
    config->dongle_cooldown = atoi(argv[7]);
    config->scheduler = argv[8];
    
    pthread_mutex_init(&config->print_mutex, NULL);
    pthread_cond_init(&config->dongles_cond, NULL);
    pthread_mutex_init(&config->burned_out_mutex, NULL);

    config->start_time = get_time_ms();
    config->burned_out = 0;

    return (config);
}