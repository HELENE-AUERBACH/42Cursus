/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:03:44 by hauerbac          #+#    #+#             */
/*   Updated: 2024/04/08 15:34:28 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	is_dead(t_philosopher *philosopher)
{
	unsigned int	boolean;

	if (pthread_mutex_lock(philosopher->dead_mutex) != 0)
		write(2, "dead_mutex lock error\n", 22);
	boolean = *(philosopher->is_dead);
	if (pthread_mutex_unlock(philosopher->dead_mutex) != 0)
		write(2, "dead_mutex unlock error\n", 24);
	return (boolean);
}

void	print_message(char *str, t_philosopher *philosopher)
{
	size_t	time;

	if (is_dead(philosopher))
		return ;
	time = get_time_in_ms() - philosopher->start_time;
	if (pthread_mutex_lock(philosopher->write_mutex) == 0)
	{
		printf("%zu %d %s\n", time, philosopher->id, str);
		if (pthread_mutex_unlock(philosopher->write_mutex) != 0)
			write(2, "write_mutex unlock error\n", 25);
	}
	else
		write(2, "write_mutex lock error\n", 23);
}

size_t	get_time_in_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday function call error\n", 33);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	let_sleep_in_ms(size_t milliseconds, t_philosopher *philosopher)
{
	size_t	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() < start_time + milliseconds
		&& is_dead(philosopher) == 0)
	{
		usleep(1200);
	}
	return (0);
}
