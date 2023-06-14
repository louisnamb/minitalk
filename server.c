#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <sys/types.h>

/*
gcc server.c libft/ft_atoi.c libft/ft_memset.c printf/ft_printf.c printf/ft_strlen.c printf/hexchars.c printf/putchars.c -o server
*/

static void bit2char(int byte[])
{
	int		i;
	char	sum;
    int		placeval;

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
	int	i;

	i = 0;
	while (byte[i] == 0)		
		i++;
	return (i == 8);	
}

static void get_bit(int signals)
{
	int			num[8];
	static int	index;

	if (index == 8)
		index = 0;
	num[index] = (signals == 31);
	index++;
	if (index == 8)
	{
		bit2char(num);
		if (end(num))
			return ;
	}
}

int main()
{
    pid_t	pid;
	struct sigaction sa;

    pid = getpid();
    ft_printf("%d\n", pid);	
	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = get_bit;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}
