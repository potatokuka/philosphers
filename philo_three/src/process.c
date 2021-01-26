/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:19:02 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 14:19:03 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <pthread/pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

static void	free_me(t_data *data)
{
	free(data->full);
	free(data->pids);
	free(data->philos);
}

static void	kill_proc(t_data *data)
{
	int			i;
	pid_t		pid;

	i = 0;
	while (i < data->num_philo)
	{
		kill(data->pids[i], SIGTERM);
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		(void)waitpid(data->pids[i], &pid, 0);
		i++;
	}
	free_me(data);
	exit(0);
}

void		*full_stomach(void *arg)
{
	t_data		*data;
	int			i;

	i = 0;
	data = arg;
	while (i < data->num_philo)
	{
		sem_wait(data->full[i]);
		i++;
	}
	sem_post(data->stop);
	return (NULL);
}

void		start_proc(t_data *data)
{
	int				i;
	int				pid;
	pthread_t		thread;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_philo)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (!pid)
			action(&data->philos[i]);
		data->pids[i] = pid;
		i++;
	}
	pthread_create(&thread, NULL, full_stomach, data);
	pthread_detach(thread);
	sem_wait(data->stop);
	kill_proc(data);
}
