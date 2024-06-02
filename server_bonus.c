/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:50:20 by trazanad          #+#    #+#             */
/*   Updated: 2024/06/02 19:21:28 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_list	*list = 0;

static int	print_msg(t_list *list)
{
    char	c;

    while (list)
    {
        c = list->content;
        write(1, &c, 1);
        list = list->next;
    }
    return (1);
}

static int	process_msg(int signum)
{
	static	unsigned	int		i = 8;
	static	unsigned	char	character = 0;

	if (i > 0)
	{
		i--;
		if (signum == SIGUSR2)
			character |= 1 << i;
	}
	if (i == 0)
	{
        ft_lstadd_back(&list, ft_lstnew(character));
        if (character == 0)
        if (print_msg(list))
            ft_lstclear(&list);
		i = 8;
		character = 0;
	}
	return (1);
}

static void	handle_sigusr(int signum, siginfo_t *info, void *context)
{
	int	res;

	res = -1;
    (void)context;
    if (info->si_pid > 0)
    {
         if (signum != SIGUSR1 && signum != SIGUSR2)
        {
            ft_putstr_fd("Error invalid signal from client!", 2);
            ft_lstclear(&list);
            exit(EXIT_FAILURE);
        }
        if (process_msg(signum))
	        res = kill(info->si_pid, signum);
        if (res < 0)
        {
            ft_putstr_fd("Error occured when sending signals!", 2);
            ft_lstclear(&list);
            exit(EXIT_FAILURE);
        }
    }
}
 
int	main(void)
{
	pid_t				pid;
	struct	sigaction	sa;

	pid = getpid();
    if (pid < 0)
    {
		ft_putstr_fd("Error invalid pid!", 2);
        exit(EXIT_FAILURE);
    }
	ft_putstr_fd("Listening on pid ",1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd(" ...\n", 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr;
    if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
    {
        ft_putstr_fd("Error with SIGUSR signal!", 2);
        exit(EXIT_FAILURE);
    }
	while(1)
    	pause();
    return (0);
}
