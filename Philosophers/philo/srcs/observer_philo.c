/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:21:07 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/24 17:55:07 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	is_this_philosopher_dead(t_philosopher *philosopher)
{
	unsigned int	boolean;

	boolean = 0;
	pthread_mutex_lock(philosopher->meal_mutex);
	if (get_current_time_in_ms() - philosopher->last_meal_time >= \
		philosopher->time_to_die && philosopher->is_eating == 0)
		boolean = 1;
	pthread_mutex_unlock(philosopher->meal_mutex);
	return (boolean);
}

static int	did_a_philosopher_die(t_simulation *simulation)
{
	size_t	i;

	i = 0;
	while (i < simulation->philosophers[0].nb_of_philosophers)
	{
		if (is_this_philosopher_dead(&simulation->philosophers[i]) == 1)
		{
			print_message("died", &simulation->philosophers[i]);
			pthread_mutex_lock(&simulation->dead_mutex);
			simulation->philosophers[i].is_dead = 1;
			simulation->is_a_dead_philo = 1;
			pthread_mutex_unlock(&simulation->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	did_all_philosophers_eat(t_simulation *simulation)
{
	size_t	i;
	size_t	total;

	i = 0;
	total = 0;
	if (simulation->philosophers[0].nb_times_must_eat == 0)
		return (0);
	while (i < simulation->philosophers[0].nb_of_philosophers)
	{
		pthread_mutex_lock(&simulation->meal_mutex);
		if (simulation->philosophers[i].eaten_meals >= \
			simulation->philosophers[i].nb_times_must_eat)
			total++;
		pthread_mutex_unlock(&simulation->meal_mutex);
		i++;
	}
	if (total == simulation->philosophers[0].nb_of_philosophers)
	{
		simulation->did_all_philos_eat = 1;
		return (1);
	}
	return (0);
}

void	*observer_routine(void *simulation_ptr)
{
	t_simulation	*simulation;

	simulation = (t_simulation *) simulation_ptr;
	while (1)
	{
		if (did_a_philosopher_die(simulation) == 1
			|| did_all_philosophers_eat(simulation) == 1)
			break ;
	}
	return (simulation_ptr);
}
