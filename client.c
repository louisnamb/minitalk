#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>

/* Ssshhh! Global variables!	We need
	 these so that main() and sh1 & sh2
	 can communicate. */
int main(int argc, char **argv)
{
	/* Get p1's process ID. */
	if (argc != 3)
		return (1);
	pid_t pid = ft_atoi(argv[1]);
	
	/* Signal setup */
	struct sigaction sa = { 0 };
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);

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
	bin2char function;
	/* Print char to bits function */

	return 0;
}