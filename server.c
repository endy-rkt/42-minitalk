/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:50:20 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/23 00:25:20 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void handle_sigusr(int signum, siginfo_t *info, void *context)
{
	static unsigned int i = 8;
	static unsigned char character = 0;
	unsigned char tmp;

	tmp = 1;
	if (i > 0)
	{
		i--;
		if (signum == SIGUSR2)
			character |= tmp << i; 
	}
	if (i == 0)
	{
		write(1,&character,1);
		usleep(42);//
		i = 8;
		character = 0;
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;
	struct sigaction sa;
	
	pid = getpid();
	printf("%d\n",pid);
	sa.sa_sigaction = &handle_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	//listen for client signal
	//print message
	//wait infinitly for signal
	while(1);
	return (0);
}