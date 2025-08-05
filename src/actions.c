/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:08:14 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/06/06 13:56:15 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	solo_philo(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	usleep(philo->data->death_time * 1000);
	print_status(philo, DIED);
}

int	rest(t_philo *philo)
{
	print_status(philo, SLEEPING);
	ft_usleep(philo->data->sleep_time, philo);
	if (is_dead(philo))
		return (1);
	return (0);
}

static void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
		pthread_mutex_unlock(philo->l_fork);
	else
		pthread_mutex_unlock(philo->r_fork);
	if (philo->id % 2 != 0)
		pthread_mutex_unlock(philo->r_fork);
	else
		pthread_mutex_unlock(philo->l_fork);
}

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
		pthread_mutex_lock(philo->l_fork);
	else if (!is_dead(philo))
		pthread_mutex_lock(philo->r_fork);
	print_status(philo, FORK_TAKEN);
	if (philo->data->n_philo == 1)
		return (solo_philo(philo), 1);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	print_status(philo, FORK_TAKEN);
	return (0);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->meal_m);
		philo->meals_eaten += 1;
		philo->last_meal_time = get_time();
		print_status(philo, EATING);
		pthread_mutex_unlock(&philo->meal_m);
		ft_usleep(philo->data->eat_time, philo);
	}
	else
		return (drop_forks(philo), 1);
	drop_forks(philo);
	return (0);
}
