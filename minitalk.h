/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:43:25 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/23 14:05:33 by trazanad         ###   ########.fr       */
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
	int				content;
	struct s_list	*next;
}	t_list;

#endif