/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:43:25 by trazanad          #+#    #+#             */
/*   Updated: 2024/06/08 11:21:37 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H

# define MINITALK_H

# include <fcntl.h>

# include <stdlib.h>

# include <signal.h>

# include <unistd.h>

typedef struct s_list
{
	char			content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(int content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
long	ft_atoi_s(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif