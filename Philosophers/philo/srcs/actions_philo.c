/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <hauerbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:56:29 by hauerbac          #+#    #+#             */
/*   Updated: 2024/04/08 17:47:12 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinks(t_philosopher *p)
{
	if (get_time_in_ms() - p->last_meal_time >= p->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	print_message("is thinking", p);
	while (get_time_in_ms() - p->last_meal_time < 0.9 * p->time_to_die)
		let_sleep_in_ms(1, p);
}

void	even_eats(t_philosopher *p)
{
	if (get_time_in_ms() - p->last_meal_time >= p->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	pthread_mutex_lock(p->right_fork_mutex);
	print_message("has taken a fork", p);
	pthread_mutex_lock(p->left_fork_mutex);
	print_message("has taken a fork", p);
	pthread_mutex_lock(p->meal_mutex);
	p->last_meal_time = get_time_in_ms();
	p->eaten_meals++;
	pthread_mutex_unlock(p->meal_mutex);
	print_message("is eating", p);
	let_sleep_in_ms(p->time_to_eat, p);
	pthread_mutex_unlock(p->left_fork_mutex);
	pthread_mutex_unlock(p->right_fork_mutex);
}

void	odd_eats(t_philosopher *p)
{
	if (get_time_in_ms() - p->last_meal_time >= p->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	if (p->nb_of_philosophers > 1)
		pthread_mutex_lock(p->left_fork_mutex);
	print_message("has taken a fork", p);
	pthread_mutex_lock(p->right_fork_mutex);
	print_message("has taken a fork", p);
	pthread_mutex_lock(p->meal_mutex);
	p->last_meal_time = get_time_in_ms();
	p->eaten_meals++;
	pthread_mutex_unlock(p->meal_mutex);
	print_message("is eating", p);
	let_sleep_in_ms(p->time_to_eat, p);
	pthread_mutex_unlock(p->right_fork_mutex);
	pthread_mutex_unlock(p->left_fork_mutex);
}

void	sleeps(t_philosopher *p)
{
	if (get_time_in_ms() - p->last_meal_time >= p->time_to_die
		|| is_dead(p))
	{
		return ;
	}
	print_message("is sleeping", p);
	let_sleep_in_ms(p->time_to_sleep, p);
}
