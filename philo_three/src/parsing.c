/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:18:56 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 18:16:18 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <semaphore.h>

void		init_philo(t_data *data, t_philo *philo, int id, char *str_id)
{
	char *str_res;

	philo->id = id + 1;
	philo->last_meal = 0;
	philo->num_eaten = 0;
	philo->data = data;
	philo->finished = false;
	str_res = ft_strjoin("satis", str_id);
	data->full[id] = init_sem(data, str_res, 0);
	philo->mealsfinished = data->full[id];
	free(str_res);
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
	init_data(data, ac, av);
	data->forks = init_sem(data, "forks", data->num_philo);
	data->write_lock = init_sem(data, "write_lock", 1);
	data->stop = init_sem(data, "stop", 0);
	data->full = malloc(sizeof(sem_t *) * data->num_philo);
	if (!data->full)
		handle_error(data, "malloc in FULL");
	data->pids = malloc(sizeof(int) * data->num_philo);
	if (!data->pids)
		handle_error(data, "malloc PIDS");
}
