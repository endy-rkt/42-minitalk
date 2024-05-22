/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:50:20 by trazanad          #+#    #+#             */
/*   Updated: 2024/05/22 22:42:40 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//binary to char
void	print(char *str)
{
	int i,j;
	unsigned char character,tmp;

	i = 8;
	j = 0;
	character = 0;
	tmp = 1;
	while (i > 0)
	{
		i--;
		if (str[j] == '1')
			character |= tmp << i; //character = character | tmp << i;
		j++;
	}
	printf("%c %d\n",character,character);
}

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = getpid();
	printf("%d\n",pid);
	//listen for client signal
	//print message
	//wait infinitly for signal
	print(argv[1]);
	// while(1);
	return (0);
}