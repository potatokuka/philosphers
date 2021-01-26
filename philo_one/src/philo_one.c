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
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo_one.h"

void			notify(t_data *data, int id, char *note, bool unlock)
{
	unsigned int	time;
	char			*str_time;
	char			*str_id;

	time = curr_time(data);
	str_time = ultoa(time);
	if (!str_time)
		handle_error(data, "Error with string time");
	str_id = ultoa(id);
	if (!str_id)
	{
		free(str_time);
		handle_error(data, "Error with string ID");
	}
	pthread_mutex_lock(&data->write_lock);
	ft_putstr_fd(str_time, 1);
	write(1, " ", 1);
	ft_putstr_fd(str_id, 1);
	ft_putstr_fd(note, 1);
	if (unlock)
		pthread_mutex_unlock(&data->write_lock);
	free(str_time);
	free(str_id);
}

static void		rotate_forks(t_philo *philo, pthread_mutex_t *forks, int *set)
{
	pthread_mutex_lock(&forks[set[LEFT]]);
	notify(philo->data, philo->id, " has taken a fork\n", true);
	pthread_mutex_lock(&forks[set[RIGHT]]);
	notify(philo->data, philo->id, " is eating\n", true);
	pthread_mutex_lock(&philo->eat_lock);
	philo->num_eaten++;
	philo->last_meal = curr_time(philo->data);
	pthread_mutex_unlock(&philo->eat_lock);
}

static void		leave_forks(pthread_mutex_t *forks, int *set)
{
	pthread_mutex_unlock(&forks[set[LEFT]]);
	pthread_mutex_unlock(&forks[set[RIGHT]]);
}

void			*action(void *arg)
{
	t_philo	*philo;
	int		forks[2];

	philo = arg;
	forks[LEFT] = philo->id - 1;
	if (philo->id != philo->data->num_philo)
		forks[RIGHT] = philo->id;
	else
		forks[RIGHT] = 0;
	while (1)
	{
		notify(philo->data, philo->id, " is thinking\n", true);
		rotate_forks(philo, philo->data->forks, forks);
		usleep(philo->data->time.eat * 1000);
		leave_forks(philo->data->forks, forks);
		notify(philo->data, philo->id, " is sleeping\n", true);
		usleep(philo->data->time.sleep * 1000);
	}
	return (NULL);
}
