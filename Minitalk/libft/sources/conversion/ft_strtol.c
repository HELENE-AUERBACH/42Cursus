/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:06:53 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/19 17:08:46 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "libft.h"

static unsigned int	ft_base(unsigned int *i, const char *str)
{
	unsigned int	base;

	base = 0;
	if (str[*i] && str[*i] == '0')
	{
		while (str[*i + 1] && str[*i + 1] == '0')
			*i += 1;
		if (str[*i + 1] == '\0')
			base = 10;
		else
			*i += 1;
		if (str[*i] && str[*i] == 'b')
			base = 2;
		else if (str[*i] && (str[*i] == 'x' || str[*i] == 'X'))
			base = 16;
		else
			base = 8;
		if (str[*i] && (str[*i] == 'b' || str[*i] == 'x' \
				|| str[*i] == 'X'))
			*i += 1;
	}
	else if (str[*i])
		base = 10;
	return (base);
}

static unsigned int	ft_is_a_valid_digit_in_base(unsigned int base, \
			const char c)
{
	unsigned int	boolean;

	boolean = 0;
	if (base <= 36 && c >= 48 && ((base == 2 && c <= 49) \
		|| (base == 8 && c <= 55) || (base == 10 && c <= 57) \
		|| (base == 16 && (c <= 57 || (c >= 65 && c <= 70) \
		|| (c >= 97 && c <= 102)))))
		boolean = 1;
	return (boolean);
}

static int	ft_error_or_sign_and_base(unsigned int boundaries[2],
			unsigned int *base, unsigned int *i, const char *str)
{
	int	result;

	boundaries[0] = -1;
	boundaries[1] = -2;
	*base = 0;
	result = 1;
	*i = ft_spaces_truncating(str);
	if (str[*i] && (str[*i] == '+' || str[*i] == '-'))
	{
		if (str[*i] == '-')
			result = -1 * result;
		*i += 1;
	}
	*base = ft_base(i, str);
	if (*base > 36 || *base == 1 || *base == 0)
		result = 0;
	if (ft_is_a_valid_digit_in_base(*base, str[*i]) == 1)
		boundaries[0] = (unsigned int) *i;
	while (str[*i] && ft_is_a_valid_digit_in_base(*base, str[*i]) == 1)
		boundaries[1] = (unsigned int)((*i)++);
	if (str[*i] || *base <= 0 || boundaries[0] > boundaries[1])
		result = 0;
	return (result);
}

static long	ft_bad_result(const char *nptr, char **endptr, unsigned int i, \
		int sign)
{
	if (endptr)
		*endptr = (char *) nptr + i;
	if (sign == -1)
		return (LONG_MIN);
	return (LONG_MAX);
}

long	ft_strtol(const char *nptr, char **endptr)
{
	unsigned int	boundaries[2];
	unsigned int	base;
	unsigned int	i;
	int				sign;
	long			result;

	sign = ft_error_or_sign_and_base(boundaries, &base, &i, nptr);
	result = 0;
	if (sign == 0)
	{
		if (endptr)
			*endptr = (char *) nptr + i;
		return (0);
	}
	i = boundaries[0];
	while (i <= boundaries[1])
	{
		result = (result * base) + ft_chartodigit(nptr[i++]);
		if (result < 0)
			return (ft_bad_result(nptr, endptr, i, sign));
	}
	if (endptr)
		*endptr = (char *) nptr + i;
	return (result * sign);
}
