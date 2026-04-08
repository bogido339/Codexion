/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbougajd <mbougajd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:18:33 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/08 13:22:16 by mbougajd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void compile(t_coder *coder)
{
    print_status(coder, "is compiling");
    smart_sleep(coder->config->time_to_compile, coder->config);
    coder->compile_count += 1;
}

void debug(t_coder *coder)
{
    print_status(coder, "is debugging");
    smart_sleep(coder->config->time_to_debug, coder->config);
}

void refactor(t_coder *coder)
{
    print_status(coder, "is refactoring");
    smart_sleep(coder->config->time_to_refactor, coder->config);
}