/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   managers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:21:52 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 14:21:53 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		death(t_data *data, unsigned int res, int i)
{
	if (res > data->time.die)
	{
		notify(data, data->philos[i].id, " is dead\n", false);
		return (1);
	}
	return (0);
}

static int		manager(t_data *data)
{
	int				i;
	unsigned int	res;
	unsigned int	philo[2];

	while (1)
	{
		i = 0;
		while (i < data->num_philo)
		{
			pthread_mutex_lock(&data->philos[i].eat_lock);
			philo[0] = data->philos[i].last_meal;
			philo[1] = data->philos[i].num_eaten;
			pthread_mutex_unlock(&data->philos[i].eat_lock);
			res = curr_time(data) - philo[0];
			if (death(data, res, i))
				return (1);
			if ((int)philo[1] == data->min_meals)
				i++;
			else
				break ;
		}
		if (i == data->num_philo)
			return (0);
	}
}

int				start_threads(t_data *data)
{
	int			i;
	pthread_t	thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philo)
	{
		if (pthread_create(&thread, NULL, action, &data->philos[i]))
			handle_error(data, "Error with creating Threads.");
		pthread_detach(thread);
		i++;
		usleep(100);
	}
	return (manager(data));
}
