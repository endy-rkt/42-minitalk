/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:39:16 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/23 00:25:05 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
			kill(server_pid, SIGUSR1);// write(1, "0",1);//send 0
		else
			kill(server_pid, SIGUSR2);// write(1, "1",1);//send 1
		usleep(100);//change value
	}
		usleep(100);//change value
}

void	send_msg(pid_t server_pid, char *msg)
{
	int i;

	i = 0;
	while (msg[i])
	{
		send_character(server_pid, msg[i]);
		i++;
		// usleep();//can we take it
	}
	send_character(server_pid, '\0');//msg end
}

int main(int argc, char *argv[])
{
	pid_t server_pid;
	
	if (argc != 3)
		exit(EXIT_FAILURE);
	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
		exit(EXIT_FAILURE);
	// printf("Ready to send msg (%s) to %d",argv[2], server_pid);//
	//send_msg 4386
	send_msg(server_pid, argv[2]);
	return (0);
}