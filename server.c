#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>

/*
Server: prints PID and recieves bits, converting them to char,

Server prints PID

Client recieves PID and string, sending bits
to represent the characters. 

Server recieves it and prints it.
*/

static void get_bit(int signals)
{
	static int num[8];
	static int i = 0;
	num = { 0 };
	num[i] = signals;
	if (i == 8)
		bit2char(num);
	i++;
}

static void bit2char(int *binary)
{
	int i;
	char sum;
    int placeval;
	sum = 0;
	i = 7;
    placeval = 1;
	while (i >= 0)
	{
        sum += (binary[i]) * placeval;
		placeval = placeval * 2;
        if (i - 1 == 0)
            placeval = -128;
        i--;
    }
	write(1, &sum, 1);
}

int main()
{
	printf("hgello");
    pid_t pid;

    pid = getpid();
    ft_printf("%d\n", pid);	
	/* Check if the PID is valid */
	if (kill(pid, 0) == -1)
	{
		perror("Invalid PID");
	}
	/* Signal setup */
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = get_bit;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	// while loop that checks for signals
	while (1)
		sleep(1);
	return 0;
}
/*
Infinite while loop is happening.
*/