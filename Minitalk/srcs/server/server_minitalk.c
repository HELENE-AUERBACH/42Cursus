/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_minitalk.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:47:41 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/20 18:16:11 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_minitalk.h"

char	*g_message;

static char	*ft_strjoin_with_free(char *s1, char *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *) malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (s1_len == 0 && s2_len == 0)
		result[0] = '\0';
	else
	{
		if (s1_len > 0)
		{
			ft_strlcpy(result, s1, s1_len + 1);
			free(s1);
		}
		if (s2_len > 0)
		{
			ft_strlcpy(result + s1_len, s2, s2_len + 1);
			free(s2);
		}
	}
	return (result);
}

static int	append_char_to_str(char c)
{
	char	*message;

	message = (char *) malloc(2 * sizeof(char));
	if (!message)
	{
		write(2, "Error\n", 6);
		write(2, "Malloc error for message\n", 25);
		return (-1);
	}
	message[0] = c;
	message[1] = '\0';
	if (!g_message)
		g_message = message;
	else
		g_message = ft_strjoin_with_free(g_message, message);
	message = NULL;
	return (0);
}

static void	free_g_message(void)
{
	if (g_message)
		free(g_message);
	g_message = NULL;
}

static void	binary_digits_to_ascci_char(int sig, siginfo_t *info,
			void *context)
{
	static int	bit = 0;
	static char	converted_char;

	(void) context;
	if (bit == 0)
		converted_char = 0;
	if (sig == SIGUSR2)
		converted_char |= (1 << bit);
	if (kill(info->si_pid, SIGUSR2) == -1)
		exit (EXIT_FAILURE);
	bit++;
	if (bit == 8)
	{
		if (converted_char != '\0'
			&& append_char_to_str(converted_char) != 0)
			free_g_message();
		if (converted_char == '\0')
		{
			ft_putendl_fd(g_message, 1);
			free_g_message();
			ft_putendl_fd("Waiting for a message...", 1);
		}
		bit = 0;
	}
}

int	main(void)
{
	char				*pid;
	struct sigaction	s1;

	g_message = NULL;
	pid = ft_itoa((int) getpid());
	write(1, "PID: ", 5);
	ft_putendl_fd(pid, 1);
	if (pid)
		free(pid);
	pid = NULL;
	sigemptyset(&s1.sa_mask);
	s1.sa_flags = SA_RESTART | SA_SIGINFO;
	s1.sa_sigaction = &binary_digits_to_ascci_char;
	ft_putendl_fd("Waiting for a message...", 1);
	while (1)
	{
		if (sigaction(SIGUSR1, &s1, NULL) == -1)
			exit (EXIT_FAILURE);
		if (sigaction(SIGUSR2, &s1, NULL) == -1)
			exit (EXIT_FAILURE);
	}
	return (0);
}
