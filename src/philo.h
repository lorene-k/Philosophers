/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhalifa <lkhalifa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:22:45 by lkhalifa          #+#    #+#             */
/*   Updated: 2024/06/13 12:35:17 by lkhalifa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

/* ------------  LIBRARIES  ------------------------------------------------ */
# include <errno.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* ------------  MACROS  --------------------------------------------------- */
/* PHILO ACTIONS */
# define FORK_TAKEN "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

/* ERR MESSAGES */
# define INV_ARG_N "Error : invalid number of arguments\n"
# define INV_CHAR "Error : invalid character\n"
# define INV_ARGS "Error : invalid argument(s)\n"
# define TIME_ERR "Error : gettimeofday() crashed\n"
# define MALLOC_ERR "Error : memory can't be allocated\n"

/* ------------  STRUCTS  -------------------------------------------------- */
typedef struct s_data
{
	int				n_philo;
	int				dead_i;
	long long		death_time;
	int				eat_time;
	int				sleep_time;
	long long		start_time;
	int				meals_to_eat;
	pthread_mutex_t	start_m;
	pthread_mutex_t	dead_m;
	pthread_mutex_t	print_m;
}					t_data;

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				meals_eaten;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}					t_philo;

typedef struct s_prog
{
	t_data			*data;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}					t_prog;

/* ------------  FUNCTIONS  ------------------------------------------------ */
/* UTILS */
long long			get_time(void);
void				print_status(t_philo *philo, char *s);
void				ft_usleep(int ms, t_philo *philo);
int					ft_atoi(const char *str);

/* CHECK & INIT */
int					check_args(int ac, char **av);
int					init_structs(int ac, char **av, t_data *data, t_prog *prog);

/* ACTIONS */
int					rest(t_philo *philo);
int					eat(t_philo *philo);

/* INIT_THREADS */
int					is_dead(t_philo *philo);
int					init_threads(t_prog *prog);

/* ERRORS */
void				check_thread(t_prog *prog, int ret);
void				check_join(t_prog *prog, int ret);
void				clean_all(t_prog *prog);
void				clean_init(t_prog *prog);

/* MONITOR */
void				monitor(t_prog *prog, t_data *data);

#endif //PHILO_H
