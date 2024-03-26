/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:54:44 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/21 18:55:19 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned int	ft_spaces_truncating(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i]
		&& (str[i] == ' ' || str[i] == '\f'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\t' || str[i] == '\v'))
		i++;
	return (i);
}

static int	ft_error_or_sign(int *sign, unsigned int boundaries[2],
		const char *str)
{
	int				result;
	unsigned int	i;

	result = 0;
	boundaries[0] = -1;
	boundaries[1] = -2;
	i = ft_spaces_truncating(str);
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	if (str[i] && str[i] >= 48 && str[i] <= 57)
		boundaries[0] = (unsigned int) i;
	while (str[i] && result == 0)
	{
		if (str[i] >= 48 && str[i] <= 57)
			boundaries[1] = (unsigned int) i++;
		else
			result = -1;
	}
	if (boundaries[0] > boundaries[1])
		result = -1;
	return (result);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	boundaries[2];
	unsigned int	i;
	int				sign;
	int				result;

	result = 0;
	sign = 1;
	if (ft_error_or_sign(&sign, boundaries, nptr) < 0)
		return (-1);
	else
	{
		i = boundaries[0];
		result = nptr[i++] - 48;
		while (i <= boundaries[1])
			result = (result * 10) + (nptr[i++] - 48);
		result *= sign;
	}
	return (result);
}

int	check_args_are_valid(size_t args[5], int argc, char **argv)
{
	int	i;
	int	result;
	int	digit_to_char;

	i = 1;
	result = 0;
	while (i < argc)
	{
		args[i] = 0;
		if (!argv[i] || argv[i][0] == '\0' || argv[i][0] == '-'
			|| (i < 5 && argv[i][0] == '0' && argv[i][1] == '\0')
			|| ft_atoi(argv[i]) < 0)
		{
			digit_to_char = (i + 1) + '0';
			write(2, "Wrong ", 6);
			write(2, &digit_to_char, 1);
			write(2, "th argument value\n", 18);
			result = -1;
		}
		else
			args[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	return (result);
}
