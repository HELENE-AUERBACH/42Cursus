/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <hauerbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:56:29 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/28 20:29:33 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinks(t_philosopher *p)
{
	if (get_current_time_in_ms() - p->last_meal_time >= p->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	print_message("is thinking", p);
	while ((p->id % 2 != 0 \
			&& get_current_time_in_ms() - p->last_meal_time < \
				(2 * p->time_to_eat) + p->time_to_sleep) \
			|| (p->id % 2 == 0 && get_current_time_in_ms() - \
				p->last_meal_time < (3 * p->time_to_eat)))
	{
		if (get_current_time_in_ms() - p->last_meal_time >= \
			p->time_to_die || is_dead(p))
			break ;
		else
			ft_usleep(1, p);
	}
}

void	even_eats(t_philosopher *philosopher)
{
	if (get_current_time_in_ms() - philosopher->last_meal_time >= \
		philosopher->time_to_die || is_dead(philosopher))
	{
		return ;
	}
	pthread_mutex_lock(philosopher->right_fork_mutex);
	print_message("has taken a fork", philosopher);
	pthread_mutex_lock(philosopher->left_fork_mutex);
	print_message("has taken a fork", philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	philosopher->last_meal_time = get_current_time_in_ms();
	philosopher->is_eating = 1;
	pthread_mutex_unlock(philosopher->meal_mutex);
	print_message("is eating", philosopher);
	ft_usleep(philosopher->time_to_eat, philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	philosopher->is_eating = 0;
	philosopher->eaten_meals++;
	pthread_mutex_unlock(philosopher->meal_mutex);
	pthread_mutex_unlock(philosopher->left_fork_mutex);
	pthread_mutex_unlock(philosopher->right_fork_mutex);
}

void	odd_eats(t_philosopher *philosopher)
{
	if (get_current_time_in_ms() - philosopher->last_meal_time >= \
		philosopher->time_to_die || is_dead(philosopher))
	{
		return ;
	}
	if (philosopher->nb_of_philosophers > 1)
		pthread_mutex_lock(philosopher->left_fork_mutex);
	print_message("has taken a fork", philosopher);
	pthread_mutex_lock(philosopher->right_fork_mutex);
	print_message("has taken a fork", philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	philosopher->last_meal_time = get_current_time_in_ms();
	philosopher->is_eating = 1;
	pthread_mutex_unlock(philosopher->meal_mutex);
	print_message("is eating", philosopher);
	ft_usleep(philosopher->time_to_eat, philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	philosopher->is_eating = 0;
	philosopher->eaten_meals++;
	pthread_mutex_unlock(philosopher->meal_mutex);
	pthread_mutex_unlock(philosopher->right_fork_mutex);
	pthread_mutex_unlock(philosopher->left_fork_mutex);
}

void	sleeps(t_philosopher *philosopher)
{
	if (get_current_time_in_ms() - philosopher->last_meal_time >= \
		philosopher->time_to_die || is_dead(philosopher))
	{
		return ;
	}
	print_message("is sleeping", philosopher);
	ft_usleep(philosopher->time_to_sleep, philosopher);
}
