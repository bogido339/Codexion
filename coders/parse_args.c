/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohamed <mohamed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 14:56:51 by username          #+#    #+#             */
/*   Updated: 2026/04/28 11:49:24 by mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	safe_atoi(const char *str, int *out)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (!is_number(str))
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > INT_MAX)
			return (0);
		i++;
	}
	*out = (int)result;
	return (1);
}

int	validate_numbers(char **argv)
{
	int	i;
	int	value;

	i = 1;
	while (i < 8)
	{
		if (!safe_atoi(argv[i], &value))
			return (0);
		if (i != 7 && value <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	validate_scheduler(const char *scheduler)
{
	return (!strcmp(scheduler, "fifo") || !strcmp(scheduler, "edf"));
}

int	parse_args(int argc, char **argv)
{
	if (argc != 9)
	{
		fprintf(stderr, "Error: wrong number of arguments\n");
		return (0);
	}
	if (!validate_numbers(argv))
	{
		fprintf(stderr, "Error: invalid numeric arguments\n");
		return (0);
	}
	if (!validate_scheduler(argv[8]))
	{
		fprintf(stderr, "Error: invalid scheduler (use 'fifo' or 'edf')\n");
		return (0);
	}
	return (1);
}
