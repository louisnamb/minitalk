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

#include "minitalk.h"

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
		(*string)[(*pos)] = '\0';
		write(1, *string, (*pos + 1));
		free(*string);
		*string = NULL;
		*index = 0;
		*pos = 0;
	}
	return (i == 8);
}

char	*ft_realloc(char **str, long *size, int pos)
{
	size_t	i;
	char	*new_str;

	i = 0;
	if ((*size) == pos || (*size) >= 50)
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

static void	get_bit(int signals, siginfo_t *info, void *content)
{
	int			num[8];
	static int	index;
	static long	max;
	static char	*string;
	static int	pos;

	if (max == 0 || pos == max)
		string = ft_realloc(&string, &max, pos);
	num[index++] = (signals == 31);
	if (index == 8 && pos < max)
	{
		index = 0;
		string[pos++] = bit2char(num);
		if (end(num, &string, &pos, &index))
		{
			max = 0;
			kill(info->si_pid, SIGUSR1);
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
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_bit;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}
