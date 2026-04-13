/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:18:33 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/13 16:38:51 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void compile(t_coder *coder)
{
    print_status(coder, "is compiling", 1);
    smart_sleep(coder->config->time_to_compile, coder);
    pthread_mutex_lock(&coder->config->monitor_mutex);
    coder->compile_count += 1;
    pthread_mutex_unlock(&coder->config->monitor_mutex);
}

void debug(t_coder *coder)
{
    print_status(coder, "is debugging", 1);
    smart_sleep(coder->config->time_to_debug, coder);
}

void refactor(t_coder *coder)
{
    print_status(coder, "is refactoring", 1);
    smart_sleep(coder->config->time_to_refactor, coder);
}