/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 21:02:18 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/06/13 12:36:30 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_prog *prog, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		prog->philo[i].id = i + 1;
		prog->philo[i].last_meal_time = get_time();
		prog->philo[i].meals_eaten = 0;
		prog->philo[i].l_fork = &prog->forks[i];
		prog->philo[i].r_fork = &prog->forks[(i + 1) % data->n_philo];
		prog->philo[i].data = data;
		i++;
	}
}

static void	init_locks(t_data *data, t_prog *prog)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&prog->forks[i], NULL);
		pthread_mutex_init(&prog->philo[i].meal_m, NULL);
		i++;
	}
	pthread_mutex_init(&data->dead_m, NULL);
	pthread_mutex_init(&data->print_m, NULL);
	pthread_mutex_init(&data->start_m, NULL);
}

static int	get_memory(t_prog *prog, t_data *data)
{
	prog->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!prog->philo)
		return (printf(MALLOC_ERR), clean_init(prog), 1);
	prog->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!prog->forks)
		return (printf(MALLOC_ERR), clean_init(prog), 1);
	return (0);
}

static void	init_data(int ac, char **av, t_data *data)
{
	data->n_philo = ft_atoi(av[1]);
	data->death_time = (long long)ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->start_time = get_time();
	data->dead_i = -1;
	if (ac == 6)
		data->meals_to_eat = ft_atoi(av[5]);
	else
		data->meals_to_eat = -1;
}

int	init_structs(int ac, char **av, t_data *data, t_prog *prog)
{
	prog->data = data;
	init_data(ac, av, data);
	if (get_memory(prog, data))
		return (1);
	init_locks(data, prog);
	init_philos(prog, data);
	return (0);
}
