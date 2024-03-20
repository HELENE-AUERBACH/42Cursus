/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spaces_truncating.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 19:56:54 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/19 19:57:46 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_spaces_truncating(const char *str)
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
