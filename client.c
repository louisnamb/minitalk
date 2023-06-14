#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <sys/types.h>

/*
gcc client.c libft/ft_atoi.c libft/ft_memset.c printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c printf/putchars.c -o client

Client: Takes PID and string, converting each char to binary
and sending that to the server.

✅ Server prints PID

✅ Client uses PID and string, sending bits
to represent the characters. 

✅ Server recieves it and prints it.
*/

int main(int argc, char **argv)
{
	/* Get p1's process ID. */
	if (argc != 3)
		return (1);
	pid_t pid = ft_atoi(argv[1]);
	
	/* Signal setup */
	int i = 0;
	int shift = 7;
	int stop = 0;
	/* Check if the PID is valid */
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
			printf("%d\n", (argv[2][i] >> shift) & 1);
			if (((argv[2][i] >> shift) & 1) == 1)
				kill(pid, SIGUSR2); //31
	
			else
				kill(pid, SIGUSR1); //30
			usleep(1000);
			shift--;
		}
		printf("\n");
		i++;
	}
	while (stop < 8)
	{
		kill(pid, SIGUSR1);
		usleep(1000);
		stop++;
	}
	/* Send the string passed to the server */
	return 0;
}