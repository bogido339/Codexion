/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:31:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/12 10:38:34 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int main(int argc, char **argv)
{
    t_config *config;
    t_dongle *dongles;
    t_coder *coders;

    if (!parse_args(argc, argv))
        return (1);

    config = fill_config(argv);

    dongles = init_dongles(config);
    if (!dongles)
        return (1);

    coders = init_coders(config);
    if (!coders)
        return (1);
    start_threads(config);
    // start_monitor(config);

    return (0);
}