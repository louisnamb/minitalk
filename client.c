#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <sys/types.h>

/*
gcc client.c libft/ft_atoi.c libft/ft_memset.c printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c printf/putchars.c -o client
*/

int main(int argc, char **argv)
{
	int		i;
	int		shift;
	int		stop;
	pid_t	pid;

	pid = ft_atoi(argv[1]);
	i = 0;
	shift = 7;
	stop = 0;
	if (argc != 3)
		return (1);
	if (kill(pid, 0) == -1)
	{
		perror("Invalid PID");
		exit(1);
	}
	while (argv[2][i])
	{
		shift = 7;
		while (shift >= 0)
		{
			if (((argv[2][i] >> shift) & 1) == 1)
				kill(pid, SIGUSR2);
	
			else
				kill(pid, SIGUSR1);
			usleep(50);
			shift--;
		}
		i++;
	}
	while (stop < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
		stop++;
	}
	return 0;
}