/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:50:20 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/26 01:17:00 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void print(t_list *list)
{
    char c;

    while (list)
    {
        c = list->content;
        write(1,&c,1);
        list = list->next;
    }
    ft_lstclear(&list);
}
void handle_sigusr(int signum, siginfo_t *info, void *context)
{
	static unsigned int i = 8;
	static unsigned char character = 0;
    static t_list *list = 0;
	
    (void)context;
        if (signum != SIGUSR1 && signum != SIGUSR2)
        {
            write (1, "Error invalid signal from client!", 33);
            exit(EXIT_FAILURE);
        }
	    if (i > 0)
	    {
	    	i--;
	    	if (signum == SIGUSR2)
	    		character |= 1 << i;
	    }
	    if (i == 0)
	    {
	    	// write(1,&character,1);
            ft_lstadd_back(&list, ft_lstnew(character));
            if (character == 0)
            print(list);
	    	i = 8;
	    	character = 0;
	    }
		if (signum == SIGUSR1 || signum == SIGUSR2)
		{
			usleep(100);
			kill(info->si_pid, signum);
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
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sigusr;
    if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
    {
        write(1, "Error with SIGUSR signal!", 25);
        exit(EXIT_FAILURE);
    }
	while(1)
	pause();
    return (0);
}
