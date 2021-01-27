/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_three.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: greed <greed@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/26 14:19:39 by greed         #+#    #+#                 */
/*   Updated: 2021/01/26 18:17:04 by greed         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

/*
** SYSTEM LIBS
*/

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <semaphore.h>

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
	sem_t				*stop;
	sem_t				**full;
	size_t				start_time;
	int					num_philo;
	int					*pids;
	t_time				time;
	int					min_meals;
	bool				need_eat;
};

sem_t					*init_sem(t_data *data, char *name, int val);
void					init_philo(t_data *data, t_philo *philo, \
									int id, char *str_id);
void					*action(void *arg);
void					start_proc(t_data *data);
char					*ultoa(unsigned long number);
int						ft_atoi(const char *str);
void					parse_data(t_data *data, int ac, char **av);
unsigned long			get_time(void);
unsigned long			curr_time(t_data *data);
void					handle_error(t_data *data, char *msg);
void					parse_input(t_data *data, int ac, char **av);
void					notify(t_data *data, int id, char *note, bool unlock);
void					ft_putstr_fd(char *str, int fd);
size_t					ft_strlen(const char *str);
char					*ft_strjoin(char const *s1, char const *s2);
bool					is_number(char *str);

#endif
