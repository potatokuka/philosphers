/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:22:01 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 17:13:46 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t		ft_strlen(char *str)
{
	int	i;

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

void		handle_error(t_data *data, char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(data);
	exit(1);
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
