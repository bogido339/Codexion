/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:18:33 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/19 18:57:46 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void compile(t_coder *coder)
{
    print_status(coder, "is compiling", 1);
    increment_compile_count(coder);
    update_compile_time(coder);
    smart_sleep(coder->config->time_to_compile, coder);
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
