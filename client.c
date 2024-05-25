/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:39:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/26 01:27:11 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void    send_signal(pid_t server_pid, int signum)
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
}

void	send_character(pid_t server_pid, char character)
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
		pause();
		usleep(100);
	}
}

void	send_msg(pid_t server_pid, char *msg)
{
	int i;

	i = 0;
	while (msg[i])
	{
		send_character(server_pid, msg[i]);
		usleep(100);
		i++;
	}
	send_character(server_pid, '\0');//msg end
}

void handle_sigusr(int signum, siginfo_t *info, void *context)
{
	(void)context;
		if (signum ==  SIGUSR1 || signum == SIGUSR2)
		{
			ft_putnbr_fd(signum ,1);
			write(1,"\n",1);
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
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr;
    if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
    {
        write(1, "Error with SIGUSR signal!", 25);
        exit(EXIT_FAILURE);
    }
	send_msg(server_pid, argv[2]);
	return (0);
}
