/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:56:29 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/24 18:59:57 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinks(t_philosopher *philosopher)
{
	print_message("is thinking", philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	while (get_current_time_in_ms() - philosopher->last_meal_time < 0.9 \
		* philosopher->time_to_die)
		ft_usleep(1, philosopher);
	pthread_mutex_unlock(philosopher->meal_mutex);
}

void	even_eats(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->right_fork_mutex);
	print_message("has taken a fork", philosopher);
	pthread_mutex_lock(philosopher->left_fork_mutex);
	print_message("has taken a fork", philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	philosopher->last_meal_time = get_current_time_in_ms();
	philosopher->is_eating = 1;
	philosopher->eaten_meals++;
	pthread_mutex_unlock(philosopher->meal_mutex);
	print_message("is eating", philosopher);
	ft_usleep(philosopher->time_to_eat, philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	philosopher->is_eating = 0;
	pthread_mutex_unlock(philosopher->meal_mutex);
	pthread_mutex_unlock(philosopher->left_fork_mutex);
	pthread_mutex_unlock(philosopher->right_fork_mutex);
}

void	odd_eats(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork_mutex);
	print_message("has taken a fork", philosopher);
	if (philosopher->nb_of_philosophers == 1)
	{
		ft_usleep(philosopher->time_to_die, philosopher);
		pthread_mutex_unlock(philosopher->left_fork_mutex);
		pthread_mutex_lock(philosopher->dead_mutex);
		philosopher->is_dead = 1;
		pthread_mutex_unlock(philosopher->dead_mutex);
		return ;
	}
	pthread_mutex_lock(philosopher->right_fork_mutex);
	print_message("has taken a fork", philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	philosopher->last_meal_time = get_current_time_in_ms();
	philosopher->is_eating = 1;
	philosopher->eaten_meals++;
	pthread_mutex_unlock(philosopher->meal_mutex);
	print_message("is eating", philosopher);
	ft_usleep(philosopher->time_to_eat, philosopher);
	pthread_mutex_lock(philosopher->meal_mutex);
	philosopher->is_eating = 0;
	pthread_mutex_unlock(philosopher->meal_mutex);
	pthread_mutex_unlock(philosopher->right_fork_mutex);
	pthread_mutex_unlock(philosopher->left_fork_mutex);
}

void	sleeps(t_philosopher *philosopher)
{
	print_message("is sleeping", philosopher);
	ft_usleep(philosopher->time_to_sleep, philosopher);
}
