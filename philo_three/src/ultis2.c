/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultis2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:19:12 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 15:27:03 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

bool		is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (true);
		i++;
	}
	return (false);
}

sem_t		*init_sem(t_data *data, char *name, int val)
{
	sem_t	*res;

	sem_unlink(name);
	res = sem_open(name, O_CREAT, 666, val);
	if (!res)
		handle_error(data, "semaphore creation");
	return (res);
}

int			ft_atoi(const char *str)
{
	int						sign;
	unsigned long int		res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = *str == '-' ? -1 : 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * (int)res);
}

char		*ultoa(unsigned long number)
{
	char			*res;
	int				size;
	unsigned long	num;

	num = number;
	size = 1;
	while (num >= 10)
	{
		num /= 10;
		size++;
	}
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (NULL);
	res[size] = '\0';
	while (size)
	{
		res[size - 1] = (number % 10) + '0';
		number /= 10;
		size--;
	}
	return (res);
}
