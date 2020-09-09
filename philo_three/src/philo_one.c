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

void	put_error(char **message)
{
	ft_putstr(message);
	write("\n");
}

int		main(char **av, int ac)
{
	if (ac != 3)
		put_error("Arg Structure: [# of philo | time to die | time to eat \
			| time to sleep[number each philo must eat]");

}
