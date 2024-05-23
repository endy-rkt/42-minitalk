/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:50:20 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/23 09:41:05 by trazanad         ###   ########.fr       */
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
		i = 8;
		character = 0;
	}
}

//handle sa with 
int main(int argc, char *argv[])
{
	pid_t pid;
	struct sigaction sa;
	
	pid = getpid();
    if (pid < 0)
    {
        write(1, "Error invalid pid!", 18);
        exit(EXIT_FAILURE);
    }
	printf("Listening on pid %d ...\n",pid);
    sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &handle_sigusr;
    if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
    {
        write(1, "Error with SIGUSR signal!", 25);
        exit(EXIT_FAILURE);
    }
	while(1);
	return (0);
}
