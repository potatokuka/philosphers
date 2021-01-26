/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:18:59 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 14:19:00 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <semaphore.h>
#include <pthread/pthread.h>

static int		death(t_philo *philo, unsigned int res)
{
	if (res > philo->data->time.die)
	{
		notify(philo->data, philo->id, " has died.\n", false);
		sem_post(philo->data->stop);
		return (1);
	}
	return (0);
}

static void		*manager(void *arg)
{
	t_philo			*philo;
	unsigned int	res;

	philo = arg;
	while (1)
	{
		sem_wait(philo->eat_lock);
		if (!philo->finished && philo->data->min_meals &&
				philo->num_eaten >= philo->data->min_meals)
		{
			sem_post(philo->mealsfinished);
			philo->finished = 1;
		}
		res = curr_time(philo->data) - philo->last_meal;
		if (death(philo, res))
			exit(0);
		sem_post(philo->eat_lock);
		usleep(500);
	}
	return (NULL);
}

static void		rotate_forks(t_philo *philo, sem_t *forks)
{
	sem_wait(forks);
	notify(philo->data, philo->id, " has taken a fork.\n", true);
	sem_wait(forks);
	notify(philo->data, philo->id, " is eating.\n", true);
	sem_wait(philo->eat_lock);
	philo->num_eaten++;
	philo->last_meal = curr_time(philo->data);
	sem_post(philo->eat_lock);
}

static void		leave_forks(sem_t *forks)
{
	sem_post(forks);
	sem_post(forks);
}

void			*action(void *arg)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = arg;
	pthread_create(&thread, NULL, manager, philo);
	pthread_detach(thread);
	while (1)
	{
		notify(philo->data, philo->id, " is thinking.\n", true);
		rotate_forks(philo, philo->data->forks);
		usleep(philo->data->time.eat * 1000);
		leave_forks(philo->data->forks);
		notify(philo->data, philo->id, " is sleeping.\n", true);
		usleep(philo->data->time.sleep * 1000);
	}
	return (NULL);
}
