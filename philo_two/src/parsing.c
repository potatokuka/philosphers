/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:22:28 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 18:22:39 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		init_philo(t_data *data, t_philo *philo, int id)
{
	philo->id = id + 1;
	philo->last_meal = 0;
	philo->num_eaten = 0;
	philo->data = data;
}

static void	init_data(t_data *data, int ac, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	if (data->num_philo < 2 || data->num_philo > 200)
		handle_error(data, "Incorrect value given for Philo's");
	data->time.die = ft_atoi(av[2]);
	if (data->time.die < 60)
		handle_error(data, "Incorrect value given for time to die: \
				must be over 60");
	data->time.eat = ft_atoi(av[3]);
	if (data->time.eat < 60)
		handle_error(data, "Incorrect value given for time to eat: \
				must be over 60");
	data->time.sleep = ft_atoi(av[4]);
	if (data->time.sleep < 60)
		handle_error(data, "Incorrect value given for time to sleep: \
				must be over 60");
	if (ac == 6)
	{
		data->min_meals = ft_atoi(av[5]);
		if (data->min_meals < 0)
			handle_error(data, "Negative Min Meals given: C'mon bro.");
	}
}

void		parse_input(t_data *data, int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (is_number(av[i]))
			handle_error(data, "Not a Numeric Input");
		i++;
	}
	if (ac < 5 || ac > 6)
		handle_error(data, "Arg Structure: [# of philo | time to die \
| time to eat | time to sleep | [number each philo must eat]");
	i = 0;
	init_data(data, ac, av);
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, 666, data->num_philo);
	if (!data->forks)
		handle_error(data, "malloc within forks");
	sem_unlink("write_lock");
	data->write_lock = sem_open("write_lock", O_CREAT, 666, 1);
}
