/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:39:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/27 22:39:17 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t handler_finished = 0;

static void   send_signal(pid_t server_pid, int signum)
{
    int res;

    res = -1;
    if (signum == SIGUSR1)
		res = kill(server_pid, SIGUSR1);
    if (signum == SIGUSR2)
		res = kill(server_pid, SIGUSR2);
    if (res < 0)
    {
        ft_putstr_fd("Error occured when sending signals!", 2);
        exit(EXIT_FAILURE);
    }
}

static void	send_character(pid_t server_pid, char character)
{
	int i;
	unsigned char tmp;

	i = 8;
	while(i > 0)
	{
        i--;
		tmp = character >> i;
		if (tmp % 2 == 0)
			send_signal(server_pid, SIGUSR1);
		else
			send_signal(server_pid, SIGUSR2);
        while (!handler_finished)
            usleep(10);
        handler_finished = 0;
	}
}

static void	send_msg(pid_t server_pid, char *msg)
{
	int i;

	i = 0;
	while (msg[i])
	{
		send_character(server_pid, msg[i]);
		i++;
	}
	send_character(server_pid, '\0');
}

static void handle_sigusr(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid > 0)
    {
		if (signum == SIGUSR1 || signum == SIGUSR2)
		{
			if (signum ==  SIGUSR1)
		    	ft_putstr_fd("0\n", 1);
	    	else if (signum == SIGUSR2)
				ft_putstr_fd("1\n", 1);
			handler_finished = 1;
		}
	}
}

int main(int argc, char *argv[])
{
	pid_t server_pid;
	struct sigaction sa;
	
	if (argc != 3)
	{
        ft_putstr_fd("Error invalid number of argument!", 2);
        exit(EXIT_FAILURE);
    }
	server_pid = ft_atoi_s(argv[1]);
	if (server_pid <= 0)
	{
        ft_putstr_fd("Error invalid pid!", 2);
        exit(EXIT_FAILURE);
    }
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr;
    if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
       	ft_putstr_fd("Error with SIGUSR signal!", 2);
        exit(EXIT_FAILURE);
    }
	send_msg(server_pid, argv[2]);
	return (0);
}
