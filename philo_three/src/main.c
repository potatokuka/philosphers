/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:18:52 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 18:24:13 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include "philo_three.h"

void	init_check(int ac)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Arg Structure: [# of philo | time to die | time to eat | \
time to sleep | [number each philo must eat]\n", 2);
		exit(1);
	}
	return ;
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
	if (!data->philos)
		handle_error(data, "malloc philosophers");
	while (i < data->num_philo)
	{
		id = ultoa(i);
		data->philos[i].eat_lock = init_sem(data, id, 1);
		init_philo(data, &data->philos[i], i, id);
		free(id);
		i++;
	}
	start_proc(data);
	return (0);
}
