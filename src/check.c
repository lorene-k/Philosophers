/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:21:35 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/05/31 16:04:17 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_arg(int ac, char **av)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) < 1 || ft_atoi(av[2]) < 0
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (printf(INV_ARGS), 1);
	if (ac == 6 && ft_atoi(av[5]) < 1)
		return (printf(INV_ARGS), 1);
	return (0);
}

static int	is_number(char *s)
{
	while (*s)
	{
		if ((*s < '0' || *s > '9'))
			return (0);
		s++;
	}
	return (1);
}

static int	is_valid_number(char **av)
{
	while (*av)
	{
		if (!is_number(*av))
			return (printf(INV_CHAR), 0);
		av++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if (!(ac == 5 || ac == 6))
		return (printf(INV_ARG_N), 1);
	if (!is_valid_number(av + 1))
		return (1);
	return (is_valid_arg(ac, av));
}
