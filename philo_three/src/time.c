/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:19:05 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 14:19:06 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"
#include <sys/time.h>

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	res;

	gettimeofday(&time, 0);
	res = time.tv_sec * 1000;
	res += time.tv_usec / 1000;
	return (res);
}

unsigned long	curr_time(t_data *data)
{
	return (get_time() - data->start_time);
}
