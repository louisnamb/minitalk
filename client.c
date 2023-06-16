/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnambaji <lnambaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:32:56 by lnambaji          #+#    #+#             */
/*   Updated: 2023/06/16 15:42:39 by lnambaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <sys/types.h>

void	helperfunc(int pid, char c, int stop)
{
	int	shift;

	shift = 7;
	while (shift >= 0)
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

int	main(int argc, char **argv)
{
	int		i;
	pid_t	pid;

	pid = ft_atoi(argv[1]);
	i = 0;
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
