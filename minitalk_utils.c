/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:54:13 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/24 10:18:16 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_count_len(char *s)
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

long	ft_atoi(const char *nptr)
{
	int		i;
	long	res;
	int		neg;

	res = 0;
	i = 0;
	neg = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		neg = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * neg);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			ft_lstlast(*lst)-> next = new;
		else
			*lst = new;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;
	t_list	*next;

	if (lst && *lst)
	{
		tmp = *lst;
		while (tmp)
		{
			next = tmp -> next;
			free(tmp);
			tmp = next;
		}
		*lst = 0;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		if (lst -> next)
			return (ft_lstlast(lst -> next));
		else
			return (lst);
	}
	return (0);
}

t_list	*ft_lstnew(int content)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (0);
	tmp -> content = content;
	tmp -> next = 0;
	return (tmp);
}
