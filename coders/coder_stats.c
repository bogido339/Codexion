/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_stats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:07:44 by mohamed           #+#    #+#             */
/*   Updated: 2026/04/20 07:00:29 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int get_compile_count(t_coder *coder)
{
    int count;

    pthread_mutex_lock(&coder->compile_mutex);
    count = coder->compile_count;
    pthread_mutex_unlock(&coder->compile_mutex);
    return (count);
}

void increment_compile_count(t_coder *coder)
{
    pthread_mutex_lock(&coder->compile_mutex);
    coder->compile_count++;
    pthread_mutex_unlock(&coder->compile_mutex);
}

long long get_compile_time(t_coder *coder)
{
    long long time;

    pthread_mutex_lock(&coder->compile_mutex);
    time = get_time_ms() - coder->last_compile_time;
    pthread_mutex_unlock(&coder->compile_mutex);
    return (time);
}

void update_compile_time(t_coder *coder)
{
    pthread_mutex_lock(&coder->compile_mutex);
    coder->last_compile_time = get_time_ms();
    pthread_mutex_unlock(&coder->compile_mutex);
}
