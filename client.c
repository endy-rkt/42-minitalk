/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:39:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/27 13:56:54 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t handler_finished = 0;

static int    send_signal(pid_t server_pid, int signum)
{
    int res;

    res = -1;
    if (signum == SIGUSR1)
		res = kill(server_pid, SIGUSR1);
    if (signum == SIGUSR2)
		res = kill(server_pid, SIGUSR2);
    if (res < 0)
    {
        write(1, "Error occured when sending signals!",35);
        exit(EXIT_FAILURE);
    }
	return (res);
}

static void	send_character(pid_t server_pid, char character, struct sigaction sa)
{
	int i;
	unsigned char tmp;
	int res;

	i = 8;
	res = -1;
	while(i > 0)
	{
        i--;
		tmp = character >> i;
		if (tmp % 2 == 0)
			res = send_signal(server_pid, SIGUSR1);
		else
			res = send_signal(server_pid, SIGUSR2);
        while (!handler_finished)
            usleep(10);
        handler_finished = 0;
	}
}

static void	send_msg(pid_t server_pid, char *msg,struct sigaction sa)
{
	int i;

	i = 0;
	while (msg[i])
	{
		send_character(server_pid, msg[i],sa);
		i++;
	}
	send_character(server_pid, '\0',sa);
}

static void handle_sigusr(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid > 0)
    {
        if (signum ==  SIGUSR1)
		    write(1,"0\n",3);
	    else if (signum == SIGUSR2)
		    write(1,"1\n",3);
        handler_finished = 1;
    }
}

int main(int argc, char *argv[])
{
	pid_t server_pid;
	struct sigaction sa;
	
	if (argc != 3)
	{
        write(1, "Error invalid number of argument!",33);
        exit(EXIT_FAILURE);
    }
	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
	{
        write(1, "Error invalid pid!", 18);
        exit(EXIT_FAILURE);
    }
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr;
    if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
        write(1, "Error with SIGUSR signal!", 25);
        exit(EXIT_FAILURE);
    }
	send_msg(server_pid, argv[2], sa);
	return (0);
}
