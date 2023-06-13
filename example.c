#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>

/*
gcc server.c -L printf -l ftprintf

gcc server.c libft/ft_atoi.c libft/ft_memset.c printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c printf/putchars.c -o server
gcc client.c libft/ft_atoi.c libft/ft_memset.c printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c printf/putchars.c -o client
General map of whats going on:
1. Run server.c to get the pid of the process.
2. Run client.c with the pid and string to print as an argv argument
3. Use a char to bin function to send bits (using SIGUSR1 and SIGUSR2)
over to the server.
4. The server uses a binary to char function to convert what its recieved
to readable characters.

4. the client prints it.
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void catcher( int sig ) {
    printf( "inside catcher() function sig: %d\n", sig);
}

int main( int argc, char *argv[] ) {
	int shift = 7;
    while (shift >= 0)
	{
		printf("%d", ('c' >> shift) & 1);
		shift--;
	}
    return (0);
}