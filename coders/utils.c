/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:24:13 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/08 13:35:25 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long get_time_ms(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_status(t_coder *coder, char *msg)
{
    int time_use;
    int coder_id;

    time_use = get_time_ms() - coder->config->start_time;
    coder_id = coder->id;

    printf("%d %d %s\n", time_use, coder_id, msg);
}

void smart_sleep(t_config *config)
{
    while ("hear is plase the logic")
    {
        usleep(500);
    }
}
