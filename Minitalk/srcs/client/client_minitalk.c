/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_minitalk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:08:14 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/20 16:59:24 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_minitalk.h"
#include <limits.h>

int	g_acknowledged;

static void	acknowledge(int signo)
{
	(void) signo;
	write(1, "Acknowledgement\n", 16);
	g_acknowledged = 1;
	return ;
}

static void	send_to_server_an_ascii_char_to_binary(pid_t server_pid,
			char c)
{
	int					i;
	int					current_bit;
	struct sigaction	s1;

	s1.sa_handler = &acknowledge;
	sigemptyset(&s1.sa_mask);
	s1.sa_flags = SA_RESTART;
	i = 0;
	while (i < 8)
	{
		current_bit = c & (1 << i);
		g_acknowledged = 0;
		if (current_bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (g_acknowledged == 0)
		{
			sigaction(SIGUSR2, &s1, NULL);
			usleep(1);
		}
		i++;
	}
	return ;
}

static int	not_a_valid_int(long val, char *endptr, const char *arg)
{
	int	boolean;

	boolean = 0;
	if (endptr == arg || *endptr != '\0' || val < INT_MIN || val > INT_MAX)
		boolean = 1;
	return (boolean);
}

static int	check_nb_args(const int argc, const char **argv)
{
	char	*endptr;
	long	server_pid;

	if (argc != 3)
	{
		write(2, "Error\n", 6);
		write(2, "Not enough arguments\n", 21);
		return (-1);
	}
	server_pid = ft_strtol(argv[1], &endptr);
	if (not_a_valid_int(server_pid, endptr, argv[1]))
	{
		write(2, "Error\n", 6);
		write(2, "First argument is not a valid PID\n", 34);
		return (-1);
	}
	if (argv[2][0] == '\0')
	{
		write(2, "Error\n", 6);
		write(2, "Second argument is an empty string\n", 35);
		return (-1);
	}
	return (0);
}

int	main(const int argc, const char **argv)
{
	int		server_pid;
	size_t	i;
	size_t	message_len;

	if (check_nb_args(argc, argv) != 0)
	{
		write(2, "Usage: ./client <the server PID>", 32);
		write(2, " <the string to send>\n", 22);
		return (EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	i = 0;
	message_len = ft_strlen(argv[2]);
	while (i < message_len)
	{
		send_to_server_an_ascii_char_to_binary(server_pid, argv[2][i]);
		i++;
	}
	send_to_server_an_ascii_char_to_binary(server_pid, '\0');
	return (0);
}
