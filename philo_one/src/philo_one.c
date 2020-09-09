/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/07 10:14:12 by greed         #+#    #+#                 */
/*   Updated: 2020/09/07 10:14:13 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *str)
{
	int len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while(i < len)
	{
		write(1, str[i], 1);
		i++;
	}
}

void	put_error(char **message)
{
	ft_putstr(message);
	write(1, "\n", 1);
	exit(1);
}

int		main(int av, char **av)
{
	if (ac != 3)
		put_error("Arg Structure: [# of philo | time to die | time to eat \
			| time to sleep[number each philo must eat]");
	return (0);
}
