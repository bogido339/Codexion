/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:31:50 by mbougajd          #+#    #+#             */
/*   Updated: 2026/04/28 18:01:11 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_resources(t_config *config)
{
	int	i;

	if (!config)
		return ;
	i = 0;
	while (i < config->number_of_coders)
	{
		free(config->dongles[i].heap);
		i++;
	}
	free(config->dongles);
	free(config->coders);
	free(config);
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_dongle	*dongles;
	t_coder		*coders;

	if (!parse_args(argc, argv))
		return (1);
	config = init_config(argv);
	if (!config)
		return (1);
	dongles = init_dongles(config);
	if (!dongles)
		return (1);
	coders = init_coders(config);
	if (!coders)
		return (1);
	start_threads(config);
	free_resources(config);
	return (0);
}
