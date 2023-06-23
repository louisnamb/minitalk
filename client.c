/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:32:56 by lnambaji          #+#    #+#             */
/*   Updated: 2023/06/22 11:26:40 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	helperfunc(int pid, char c, int stop)
{
	int	shift;

	shift = 7;
	while (stop == 1 && shift >= 0)
	{
		if (((c >> shift) & 1))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(50);
		shift--;
	}
	if (stop == 0)
	{	
		while (stop < 8)
		{
			kill(pid, SIGUSR1);
			usleep(50);
			stop++;
		}
	}
}

static void	recieved(int signals)
{
	(void)signal;
	write(1, "Message Recieved!\n", 18);
	exit(0);
}

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	pid = ft_atoi(argv[1]);
	i = 0;
	signal(SIGUSR1, recieved);
	if (argc != 3)
		return (1);
	if (kill(pid, 0) == -1)
	{
		perror("Invalid PID");
		exit(1);
	}
	while (argv[2][i])
	{
		helperfunc(pid, argv[2][i], 1);
		i++;
	}
	helperfunc(pid, argv[2][i], 0);
	return (0);
}
