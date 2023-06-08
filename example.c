#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>

/*
gcc server.c -L printf -l ftprintf

gcc server.c libft/ft_atoi.c printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c printf/putchars.c -o server
gcc client.c libft/ft_atoi.c printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c printf/putchars.c -o client
General map of whats going on:
1. Run server.c to get the pid of the process.
2. Run client.c with the pid and string to print as an argv argument
3. Use a char to bin function to send bits (using SIGUSR1 and SIGUSR2)
over to the server.
4. The server uses a binary to char function to convert what its recieved
to readable characters.

4. the client prints it.
*/


int main()
{
    struct sigaction sa;
    int pid = getpid();
    sa.sa_handler = sigusr1_handler;
    ft_printf("%d", pid);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGURS1, &sa, NULL) == -1)
    {
        perror("sigaction error");
        return (1);
    }
    
    return (0);
}