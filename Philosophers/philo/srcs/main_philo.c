/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:39:53 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/24 20:23:37 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosopher(t_simulation *sim, size_t i, size_t args[5],
	pthread_mutex_t *forks)
{
	sim->philosophers[i].id = i + 1;
	sim->philosophers[i].nb_of_philosophers = args[NUMBER_OF_PHILOSOPHERS];
	sim->philosophers[i].time_to_die = args[TIME_TO_DIE];
	sim->philosophers[i].time_to_eat = args[TIME_TO_EAT];
	sim->philosophers[i].time_to_sleep = args[TIME_TO_SLEEP];
	sim->philosophers[i].nb_times_must_eat = \
		args[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT];
	sim->philosophers[i].eaten_meals = 0;
	sim->philosophers[i].is_eating = 0;
	sim->philosophers[i].is_dead = 0;
	sim->philosophers[i].left_fork_mutex = &forks[i];
	if (i == 0)
		sim->philosophers[i].right_fork_mutex = \
			&forks[args[NUMBER_OF_PHILOSOPHERS] - 1];
	else
		sim->philosophers[i].right_fork_mutex = &forks[i - 1];
	sim->philosophers[i].write_mutex = &sim->write_mutex;
	sim->philosophers[i].meal_mutex = &sim->meal_mutex;
	sim->philosophers[i].dead_mutex = &sim->dead_mutex;
}

static void	*philo_routine(void *philo_ptr)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *) philo_ptr;
	if (philosopher->nb_of_philosophers == 1)
	{
		pthread_mutex_lock(philosopher->left_fork_mutex);
		print_message("has taken a fork", philosopher);
		ft_usleep(philosopher->time_to_die, philosopher);
		pthread_mutex_unlock(philosopher->left_fork_mutex);
		philosopher->is_dead = 1;
		print_message("died", philosopher);
		return (philo_ptr);
	}
	else if (philosopher->id % 2 == 0)
		ft_usleep(1, philosopher);
	while (philosopher->nb_of_philosophers > 1 && !is_dead(philosopher))
	{
		if (philosopher->id % 2 == 0)
			even_eats(philosopher);
		else
			odd_eats(philosopher);
		sleeps(philosopher);
		thinks(philosopher);
	}
	return (philo_ptr);
}

static int	create_threads(t_simulation *sim, size_t args[5],
	pthread_mutex_t *forks)
{
	pthread_t	observer;
	size_t		i;
	size_t		time_in_ms;

	time_in_ms = get_current_time_in_ms();
	i = 0;
	while (i < args[NUMBER_OF_PHILOSOPHERS])
	{
		init_philosopher(sim, i, args, forks);
		sim->philosophers[i].start_time = time_in_ms;
		sim->philosophers[i].last_meal_time = time_in_ms;
		if (pthread_create(&sim->philosophers[i].thread, NULL,
				&philo_routine, &sim->philosophers[i]) != 0)
			return (write(2, "P. thread creation error\n", 25), -2);
		i++;
	}
	if (pthread_create(&observer, NULL, &observer_routine, &sim) != 0)
		return (write(2, "Observer thread creation error\n", 31), -1);
	if (pthread_join(observer, NULL) != 0)
		return (write(2, "Join observer thread error\n", 27), -4);
	i = 0;
	while (i < args[NUMBER_OF_PHILOSOPHERS])
		if (pthread_join(sim->philosophers[i++].thread, NULL) != 0)
			return (write(2, "Join phi. thread error\n", 23), -3);
	return (0);
}

static void	destroy_simulation(t_simulation *sim, size_t args[5],
	pthread_mutex_t *forks_mutex)
{
	size_t	i;

	pthread_mutex_destroy(&sim->write_mutex);
	pthread_mutex_destroy(&sim->meal_mutex);
	pthread_mutex_destroy(&sim->dead_mutex);
	i = 0;
	while (i < args[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_mutex_destroy(&forks_mutex[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	size_t			args[5];
	size_t			i;
	t_simulation	sim;
	pthread_mutex_t	forks_mutex[NUMBER_OF_PHILO_MAX];
	t_philosopher	philosophers[NUMBER_OF_PHILO_MAX];

	if (!(argc == 5 || argc == 6))
		return (write(2, "Wrong arguments number\n", 23), -1);
	if (check_args_are_valid(args, argc, argv) < 0)
		return (-2);
	if (args[NUMBER_OF_PHILOSOPHERS] > NUMBER_OF_PHILO_MAX)
		return (write(2, "Too many philosophers\n", 22), -3);
	sim.philosophers = philosophers;
	sim.is_a_dead_philo = 0;
	sim.did_all_philos_eat = 0;
	pthread_mutex_init(&sim.write_mutex, NULL);
	pthread_mutex_init(&sim.meal_mutex, NULL);
	pthread_mutex_init(&sim.dead_mutex, NULL);
	i = 0;
	while (i < args[NUMBER_OF_PHILOSOPHERS])
		pthread_mutex_init(&forks_mutex[i++], NULL);
	if (create_threads(&sim, args, forks_mutex) < 0)
		return (destroy_simulation(&sim, args, forks_mutex), -4);
	destroy_simulation(&sim, args, forks_mutex);
	return (0);
}
