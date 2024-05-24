/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:43:25 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/24 10:15:52 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# include <stdio.h>//

# include <fcntl.h>

# include <stdlib.h>

# include <signal.h>

# include <unistd.h>

# include <string.h>//

typedef struct s_list
{
	char			content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(int content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
long	ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
int	ft_count_len(char *s);


#endif