/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:18:36 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/24 18:20:38 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# ifndef NUMBER_OF_PHILO_MAX

#  define NUMBER_OF_PHILO_MAX 200

# endif

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philosopher
{
	unsigned int	id;
	unsigned int	eaten_meals;
	unsigned int	is_eating;
	unsigned int	is_dead;
	size_t			nb_of_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nb_times_must_eat;
	size_t			start_time;
	size_t			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*dead_mutex;
}				t_philosopher;

typedef struct s_simulation
{
	unsigned int	is_a_dead_philo;
	unsigned int	did_all_philos_eat;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
	t_philosopher	*philosophers;
}				t_simulation;

enum e_args
{
	NUMBER_OF_PHILOSOPHERS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT,
};

int				check_args_are_valid(size_t args[5], int argc, char **argv);
size_t			get_current_time_in_ms(void);
int				ft_usleep(size_t milliseconds, t_philosopher *philosopher);
unsigned int	is_dead(t_philosopher *philosopher);
void			print_message(char *str, t_philosopher *philosopher);
void			*observer_routine(void *simulation_ptr);
void			thinks(t_philosopher *philosopher);
void			even_eats(t_philosopher *philosopher);
void			odd_eats(t_philosopher *philosopher);
void			sleeps(t_philosopher *philosopher);

#endif
