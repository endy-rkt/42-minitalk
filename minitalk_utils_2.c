/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:54:13 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/26 22:53:49 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

