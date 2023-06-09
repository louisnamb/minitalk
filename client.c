#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>

/*
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


	int shift = 0;
	while (argv[2][i])
	{
		shift = 7;
		while (shift >= 0)
		{
			if ((argv[2][i] >> shift) & 1)//If the LSB is 1, send signal SIGUSR1
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			shift--;
		}
		i++;
	}
	/* Send the string passed to the server */

	return 0;
}