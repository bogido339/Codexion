/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_agrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 14:56:51 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/01 14:21:17 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int is_number(char *nbr)
{
    int i;

    if (!nbr || !nbr[0])
        return (0);
    i = 0;
    while(nbr[i])
    {
        if (nbr[i] >= '0' && nbr[i] <= '9')
            i++;
        else
            return 0;
    }
    return (1);
}

int validate_numbers(char **argv)
{
    int i;

    i = 1;
    while (i < 8)
    {
        if (!is_number(argv[i]))
            return (0);
        i++;    
    }
    return (1);
}

int validate_scheduler(char *scheduler)
{
    if (!strcmp(scheduler, "fifo"))
        return (1);
    if (!strcmp(scheduler, "edf"))
        return (1);
    
    return (0);
}

int parse_args(int argc, char **argv)
{
    if (argc != 9)
        return (fprintf(stderr, "number of args in not correct"), 0);
    if (!validate_numbers(argv))
        return (fprintf(stderr, "validate number function"), 0);
    if (!validate_scheduler(argv[8]))
        return (fprintf(stderr, "validae scheduler function"), 0);
    return (1);
}

