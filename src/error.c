/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:55:39 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/06/13 12:35:30 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_thread(t_prog *prog, int ret)
{
	pthread_mutex_lock(&prog->data->print_m);
	if (ret == EAGAIN)
		printf("Error: Insufficient resources to create another thread\n");
	else if (ret == EINVAL)
		printf("Error: Invalid settings in thread attributes\n");
	else if (ret == EPERM)
		printf("Error: No permission to set scheduling policy and parameters\n");
	else
		printf("Unknown error");
	pthread_mutex_unlock(&prog->data->print_m);
}

void	check_join(t_prog *prog, int ret)
{
	pthread_mutex_lock(&prog->data->print_m);
	if (ret == ESRCH)
		printf("Error: No thread found with the specified ID\n");
	else if (ret == EINVAL)
		printf("Error: The thread is not a joinable thread\n");
	else if (ret == EDEADLK)
		printf("Error: Deadlock detected or joining itself\n");
	else if (ret == ENOMEM)
		printf("Error: Insufficient memory to join the thread\n");
	else
		printf("Unknown error");
	pthread_mutex_unlock(&prog->data->print_m);
}

void	clean_all(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->data->n_philo)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		pthread_mutex_destroy(&prog->philo[i].meal_m);
		i++;
	}
	pthread_mutex_destroy(&prog->data->dead_m);
	pthread_mutex_destroy(&prog->data->print_m);
	pthread_mutex_destroy(&prog->data->start_m);
	free(prog->philo);
	free(prog->forks);
}

void	clean_init(t_prog *prog)
{
	int	i;

	i = 0;
	if (prog->forks)
		free(prog->philo);
	if (prog->forks)
	free(prog->forks);
}