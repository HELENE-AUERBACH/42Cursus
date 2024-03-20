/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:34:07 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/19 19:55:52 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_chartodigit(const char c)
{
	unsigned int	digit;

	digit = 0;
	if (c >= '0' && c <= '9')
		digit = c - '0';
	if (c >= 'A' && c <= 'Z')
		digit = c - 'A' + 10;
	if (c >= 'a' && c <= 'z')
		digit = c - 'a' + 10;
	return (digit);
}
