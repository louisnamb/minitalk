#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <sys/types.h>

/*
gcc server.c libft/ft_atoi.c libft/ft_memset.c printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c printf/putchars.c -o server

Server: prints PID and recieves bits, converting them to char,

Server prints PID

Client recieves PID and string, sending bits
to represent the characters. 

Server recieves it and prints it.
*/

struct bytes {
	int data[8];
	struct bytes *next;
};

static void bit2char(int byte[])
{
	int i;
	char sum;
    int placeval;
	sum = 0;
	i = 7;
    placeval = 1;
	while (i >= 0)
	{
        sum += (byte[i]) * placeval;
		placeval = placeval * 2;
        if (i - 1 == 0)
            placeval = -128;
        i--;
    }
	write(1, &sum, 1);
	return ;
}

int end(int byte[])
{
	int i;

	i = 0;
	while (byte[i] == 0)		
		i++;
	return (i == 8);	
}

struct bytes	*ft_free(struct bytes *data, struct bytes *new)
{
	free(data);
	return (new);
}

static void get_bit(int signals)
{
	struct bytes *num;
	static int index = 0;
	static int arr = 0;
	int j = 0;
	num = NULL;
	if (num == NULL)
	{
		num = malloc(sizeof(num));
		num->next = NULL;
	}
	num->data[index] = (signals == 31);
	ft_printf("%d", (signals == 31));
	index++;
	if (index == 8)
	{
		ft_printf("\n");
		index = 0;
		if (!end(num->data))
		{
			printf("new node\n");
			num = ft_free(num, malloc(sizeof(num)));
		}
		else
		{
			bit2char(num->data);
			ft_free(num, NULL);
			return ;
		}
		bit2char(num->data);
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