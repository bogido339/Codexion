/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parse_args.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/03/28 14:56:51 by username         #+#    #+#              */
/*   Updated: 2026/04/26 16:27:30 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	is_number(char *nbr)
{
	int	i;

	if (!nbr || !nbr[0])
		return (0);
	i = 0;
	while (nbr[i])
	{
		if (!is_digit((unsigned char) nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

int	int_max(char *nbr)
{
	int		i = 0;
	long	result = 0;

	if (!nbr || !nbr[0])
		return (0);
	while (nbr[i])
	{
		if (!is_digit((unsigned char) nbr[i]))
			return (0);
		result = result * 10 + (nbr[i] - '0');
		if (result > 2147483647 || result < 1)
			return (0);
		i++;
	}
	return (1);
}

int	validate_numbers(char **argv)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (!is_number(argv[i]))
			return (0);
		if (!int_max(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_scheduler(char *scheduler)
{
	if (!strcmp(scheduler, "fifo"))
		return (1);
	if (!strcmp(scheduler, "edf"))
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv)
{
	if (argc != 9)
		return (fprintf(stderr, "number of args in not correct\n"), 0);
	if (!validate_numbers(argv))
		return (fprintf(stderr, "validate number function\n"), 0);
	if (atoi(argv[1]) <= 0)
		return (fprintf(stderr, "number of coder can not nigativ\n"), 0);
	if (!validate_scheduler(argv[8]))
		return (fprintf(stderr, "validate scheduler function\n"), 0);
	return (1);
}
