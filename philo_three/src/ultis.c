/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ultis.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:19:09 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 14:19:10 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <stdlib.h>
#include <pthread/pthread.h>

void	notify(t_data *data, int id, char *note, bool unlock)
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

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		i += write(fd, &str[i], len - i);
	}
}

void	handle_error(t_data *data, char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(data);
	exit(1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	k;

	k = 0;
	if (s1 == 0)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	dest = (char*)malloc(i + 1);
	if (!(dest))
		return (NULL);
	while (*s1)
	{
		dest[k] = *s1;
		s1++;
		k++;
	}
	while (*s2)
	{
		dest[k] = *s2;
		s2++;
		k++;
	}
	dest[k] = '\0';
	return (dest);
}
