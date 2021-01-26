/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:22:25 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 14:22:26 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include "philo_two.h"

void	init_check(int ac)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd(E_INPUT, 2);
		exit(1);
	}
	return ;
}

void	handle_error(t_data *data, char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free(data);
	exit(1);
}

int		main(int ac, char **av)
{
	t_data		*data;
	char		*id;
	int			i;

	i = 0;
	init_check(ac);
	data = malloc(sizeof(t_data));
	if (!data)
		handle_error(data, "malloc data");
	memset(data, 0, sizeof(t_data));
	data->start_time = get_time();
	parse_input(data, ac, av);
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	while (i < data->num_philo)
	{
		id = ultoa(i);
		sem_unlink(id);
		data->philos[i].eat_lock = sem_open(id, O_CREAT, 666, 1);
		free(id);
		init_philo(data, &data->philos[i], i);
		i++;
	}
	if (!data->philos)
		handle_error(data, "malloc philosophers");
	return (start_threads(data));
}
