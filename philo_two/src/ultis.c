/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultis.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:22:37 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 16:55:34 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdlib.h>

void		notify(t_data *data, int id, char *note, bool unlock)
{
	unsigned int	time;
	char			*str_time;
	char			*str_id;

	time = curr_time(data);
	str_time = ultoa(time);
	if (!str_time)
		handle_error(data, "string time");
	str_id = ultoa(id);
	if (!str_id)
	{
		free(str_time);
		handle_error(data, "string ID");
	}
	sem_wait(data->write_lock);
	ft_putstr_fd(str_time, 1);
	write(1, " ", 1);
	ft_putstr_fd(str_id, 1);
	ft_putstr_fd(note, 1);
	if (unlock)
		sem_post(data->write_lock);
	free(str_time);
	free(str_id);
}

size_t		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		ft_putstr_fd(char *str, int fd)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		i += write(fd, &str[i], len - i);
	}
}

int			ft_atoi(const char *str)
{
	int					sign;
	unsigned long int	res;

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
