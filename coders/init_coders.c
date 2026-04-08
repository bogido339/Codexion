/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:05:10 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/08 12:19:33 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder *init_coders(t_config *config)
{
    int num_coders = config->number_of_coders;
    int i = 0;

    t_coder *coders = malloc(sizeof(t_coder) * num_coders);
    if (!coders)
        return NULL;

    while (i < num_coders)
    {
        coders[i].id = i;
        coders[i].last_compile_time = 0;
        coders[i].compile_count = 0;
        coders[i].left_dongle = &config->dongles[i];
        coders[i].right_dongle = &config->dongles[(i + 1) % num_coders];
        coders[i].config = config;
        i++;
    }

    config->coders = coders;
    return coders;
}