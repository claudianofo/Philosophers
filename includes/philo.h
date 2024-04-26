/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:07:24 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/26 15:34:38 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include "structs.h"

//	main
void			notify(t_data *data, int id, char *action);

//	input
int				input_error(void);
bool			correct_args(int ac, char **av);

//  utils
struct timeval	make_future_timeval(struct timeval start, int wait_time);
void			wait_sleep(struct timeval start, int wait_time);
int				elapsed_time(struct timeval goal_time);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);

//  init
t_data			*init_data(char **av);
t_philo			**init_philos(t_data *data);
void			init_forks(t_data *data);

//	routine
void			one_philo_routine(t_philo *philo);
void			eat_sleep_think_routine(t_philo *philo);
void			*routine(void *philo_arg);

// exit
void			join_threads(t_data *data, int threads_created);
void			free_philos(t_data *data, int philos_created);
void			free_forks(t_data *data, int forks_created, int fork_mutexes);
void			free_data(t_data *data, int cleanup_code);

#endif