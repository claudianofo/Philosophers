/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:07:24 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/19 15:18:09 by cnorton-         ###   ########.fr       */
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

//	input
int		input_error(void);
bool	correct_args(int ac, char **av);

//  utils
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	wait_sleep(int millisec);
int		get_elapsed_time(struct timeval start_time);

//  init
t_data	*init_data(char **av);
t_philo	**init_philos(t_data *data);
void	init_forks(t_data *data);

// exit
void	join_threads(t_data *data, int threads_created);
void	free_philos(t_data *data, int philos_created);
void	free_forks(t_data *data, int forks_created, int fork_mutexes);
void	free_data(t_data *data, int cleanup_code);

#endif