/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:04:24 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/16 14:55:37 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_philo t_philo;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_data
{
	int		no_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		no_meals;
	t_philo	**philos;
	t_fork	**forks;
	struct timeval start_time;
}		t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	t_data		*data;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;


#endif