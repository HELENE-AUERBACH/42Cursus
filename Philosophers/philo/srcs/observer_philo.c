/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:21:07 by hauerbac          #+#    #+#             */
/*   Updated: 2024/04/08 18:14:47 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	did_all_philosophers_do_their_routine(t_simulation *simulation,
		size_t *total)
{
	size_t			i;
	t_philosopher	*p;

	i = 0;
	while (i < simulation->philosophers[0].nb_of_philosophers)
	{
		p = &simulation->philosophers[i];
		pthread_mutex_lock(&simulation->meal_mutex);
		if (p->nb_min_meals != 0 && p->eaten_meals >= p->nb_min_meals)
		{
			(*total)++;
		}
		if (get_time_in_ms() - p->last_meal_time >= p->time_to_die)
		{
			print_message("died", p);
			pthread_mutex_lock(&simulation->dead_mutex);
			simulation->is_a_dead_philo = 1;
			pthread_mutex_unlock(&simulation->dead_mutex);
			pthread_mutex_unlock(&simulation->meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&simulation->meal_mutex);
		i++;
	}
	return (0);
}

void	observer_routine(t_simulation *sim)
{
	size_t	total;

	while (1)
	{
		total = 0;
		if (did_all_philosophers_do_their_routine(sim, &total) == 1)
		{
			break ;
		}
		if (sim->philosophers[0].nb_min_meals != 0
			&& total == sim->philosophers[0].nb_of_philosophers)
		{
			pthread_mutex_lock(&sim->dead_mutex);
			sim->is_a_dead_philo = 1;
			pthread_mutex_unlock(&sim->dead_mutex);
			break ;
		}
		usleep(1000);
	}
	return ;
}
