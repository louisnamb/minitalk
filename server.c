/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   server.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lnambaji <lnambaji@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/06/15 15:32:50 by lnambaji		  #+#	#+#			 */
/*   Updated: 2023/06/15 15:33:56 by lnambaji		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"
#include <signal.h>
#include <sys/types.h>

static char	bit2char(int byte[])
{
	char	sum;
	int		i;

	sum = 0;
	i = 8;
	while (i-- > 0)
		sum |= (byte[i] << (7 - i));
	return (sum);
}

int	end(int byte[])
{
	int	i;

	i = 0;
	while (byte[i] == 0)
		i++;
	return (i == 8);
}

char	*ft_realloc(char *str, size_t size, size_t pos)
{
	size_t	i;
	char	*new_str;

	i = 0;
	new_str = malloc(sizeof(char) * size);
	while (str[i] && i < pos)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[size] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}

static void	get_bit(int signals)
{
	int			num[8];
	static int	index;
	static long	max;
	static char	*string;
	static int	pos;
	static int	chkr;

	if (chkr == 0)
	{
		chkr++;
		string = malloc(sizeof(char) * (max + 1));
		string[max - 1] = '\0';
		if (!string)
			return ;
	}
	num[index++] = (signals == 31);
	if (index == 8)
	{
		index = 0;
		string[pos++] = bit2char(num);
		if (end(num))
		{
			write(1, string, pos);
			free(string);
			string = NULL;
			chkr = 0;
			pos = 0;
			return ;
		}
		if (pos == max)
		{
			string = ft_realloc(string, max, pos);
			max += 50;
		}
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

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
