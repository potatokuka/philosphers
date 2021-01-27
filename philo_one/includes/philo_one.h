/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_one.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:08:46 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 18:04:19 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

/*
** SYSTEM LIBS
*/

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>

enum					e_fork
{
	LEFT,
	RIGHT,
};

typedef struct			s_time
{
	unsigned int		die;
	unsigned int		sleep;
	unsigned int		eat;
}						t_time;

typedef struct s_data	t_data;

typedef struct			s_philo
{
	int					id;
	int					num_eaten;
	size_t				last_meal;
	int					forks[2];
	t_data				*data;
	pthread_mutex_t		eat_lock;
}						t_philo;

struct					s_data
{
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	size_t				start_time;
	int					num_philo;
	t_time				time;
	int					min_meals;
	bool				need_eat;
};

void					ft_putstr_fd(char *str, int fd);
void					*action(void *arg);
int						start_threads(t_data *data);
void					init_philo(t_data *data, t_philo *philo, int id);
char					*ultoa(unsigned long number);
int						ft_atoi(const char *str);
void					parse_data(t_data *data, int ac, char **av);
unsigned long			get_time(void);
unsigned long			curr_time(t_data *data);
void					handle_error(t_data *data, char *msg);
void					notify(t_data *data, int id, char *note, bool unlock);
bool					is_number(char *str);

#endif
