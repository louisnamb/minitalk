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

int	end(int byte[], char **string, int *pos, int *index)
{
	int	i;

	i = 0;
	while (byte[i] == 0)
		i++;
	if (i == 8)
	{
	//	printf("\033[0;31mpos: %d index: %d str: %d\033[0m\n", *pos, *index, (*(string) == NULL));
		(*string)[(*pos)] = '\0';
		write(1, *string, (*pos + 1));
		free(*string);
		*string = NULL;
		*index = 0;
		*pos = 0;
	//	printf("\033[0;31mpos: %d index: %d str: %d\033[0m\n", *pos, *index, (*(string) == NULL));
	}
	return (i == 8);
}

char	*ft_realloc(char **str, long *size, int pos)
{
	size_t	i;
	char	*new_str;

	i = 0;
	if ((*size) == pos)
		*size += 50;
	new_str = malloc(sizeof(char) * ((*size) + 1));
	if (!new_str)
		return (NULL);
	while (i < pos && (*str)[i] && *size != 0)
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[(*size)] = '\0';
	if (i == pos && (*str))
	{
		free(*str);
		*str = NULL;
	}
	return (new_str);
}

static void	get_bit(int signals)
{
	int			num[8];
	static int	index;
	static long	max;
	static char	*string;
	static int	pos;

	if (max == 0 || pos == max)
	{
		printf("\033[0;31mpos: %d index: %ld str: %d\033[0m\n", pos, max, ((string) == NULL));
		string = ft_realloc(&string, &max, pos);
		max += 50;
		printf("\033[0;31mpos: %d index: %ld str: %d\033[0m\n", pos, max, ((string) == NULL));
	}
	num[index++] = (signals == 31);
	if (index == 8 && pos < max)
	{
		string[pos++] = bit2char(num);
	//	printf("\033[0;34mpos: %d\033[0m\n", pos);
		index = 0;
		if (end(num, &string, &pos, &index))
		{
			max = 0;
		//	printf("\033[0;31mmax: %ld pos: %d index: %d str: %d\033[0m\n", max, pos, index, ((string) == NULL));
			return ;
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
