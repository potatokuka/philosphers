/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:21:49 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 14:21:50 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		handle_error(data, "Allocation of Data failed");
	if (ac < 5 || ac > 6)
		handle_error(data, "Arg Structure: [# of philo | time to die | \
time to eat | time to sleep[number each philo must eat]");
	data->start_time = get_time();
	parse_data(data, ac, av);
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->philos[i].eat_lock, NULL);
		init_philo(data, &data->philos[i], i);
		i++;
	}
	if (!data->philos)
		handle_error(data, "Malloc Error with Philosophers Init");
	return (start_threads(data));
}
