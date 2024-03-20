/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hauerbac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:56:01 by hauerbac          #+#    #+#             */
/*   Updated: 2024/03/20 16:42:11 by hauerbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>

size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
unsigned int	ft_spaces_truncating(const char *str);
unsigned int	ft_chartodigit(const char c);
long			ft_strtol(const char *nptr, char **endptr);

#endif
