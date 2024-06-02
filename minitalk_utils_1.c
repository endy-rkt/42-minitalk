/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:52:07 by trazanad          #+#    #+#             */
/*   Updated: 2024/06/02 19:20:31 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_count_len(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (fd > -1 && ft_count_len(s) > 0)
		write(fd, s, ft_count_len(s));
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (fd > -1)
	{
		if (n == -2147483648)
			write(fd, "-2147483648", 11);
		else if (n < 0)
		{
			write(fd, "-", 1);
			ft_putnbr_fd(-n, fd);
		}
		else if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
			ft_putnbr_fd(n % 10, fd);
		}
		else
		{
			c = n + '0';
			write(fd, &c, 1);
		}
	}
}

long	ft_atoi_s(const char *nptr)
{
	int		i;
	long	res;

	res = 0;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	if (nptr[i])
		res = -1;
	return (res);
}
