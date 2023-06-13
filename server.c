#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <sys/types.h>

/*
Server: prints PID and recieves bits, converting them to char,

Server prints PID

Client recieves PID and string, sending bits
to represent the characters. 

Server recieves it and prints it.
*/

static void bit2char(int *binary, int array)
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

static void get_bit(int signals)
{
	static int num[1][8];
	static int index = 0;
	static int arr = 0;
	int j = 0;
	num[arr][index] = (signals == 31);
	ft_printf("%d", (signals == 31));
	index++;
	if (index == 8)
	{
		bit2char(num[arr], arr);
		index = 0;
		num[arr + 1] = malloc(sizeof(int) * 8);
		arr++;
	}
}

int main()
{
    pid_t pid;

    pid = getpid();
    ft_printf("%d\n", pid);	
	/* Signal setup */
	struct sigaction sa;
	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = get_bit;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	// while loop that checks for signals
	while (1)
		pause();
	return (0);
}
/*
Infinite while loop is happening.
*/