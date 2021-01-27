/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_two.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:22:23 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 18:09:21 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

/*
** SYSTEM LIBS
*/

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <semaphore.h>

enum						e_fork
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
	int					finished;
	t_data				*data;
	sem_t				*eat_lock;
	sem_t				*mealsfinished;
}						t_philo;

struct					s_data
{
	t_philo				*philos;
	sem_t				*forks;
	sem_t				*write_lock;
	sem_t				**full;
	sem_t				*stop;
	size_t				start_time;
	int					num_philo;
	t_time				time;
	int					min_meals;
	bool				need_eat;
};

void					*action(void *arg);
int						start_threads(t_data *data);
void					init_philo(t_data *data, t_philo *philo, int id);
char					*ultoa(unsigned long number);
int						ft_atoi(const char *str);
void					parse_data(t_data *data, int ac, char **av);
unsigned long			get_time(void);
unsigned long			curr_time(t_data *data);
void					handle_error(t_data *data, char *msg);
void					parse_input(t_data *data, int ac, char **av);
void					notify(t_data *data, int id, char *note, bool unlock);
void					ft_putstr_fd(char *str, int fd);
bool					is_number(char *str);

#endif
