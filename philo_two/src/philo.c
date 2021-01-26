/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:22:30 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 14:22:31 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

	philo = arg;
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
