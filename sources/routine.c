/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:17:33 by cnorton-          #+#    #+#             */
/*   Updated: 2024/05/02 12:24:02 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
Separate from the eat_sleep_think_routine to avoid getting stuck
before grabbing the 2nd fork
*/
void	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	notify(philo->data, philo->id, "has taken a fork");
	return ;
}

/*
The main philosopher routine - checks if the monitor has set the 
program finished flag to true. Otherwise, the philosopher loops through 
grabbing forks (and locking the forks with mutexes), eating, sleeping 
and thinking for lengths of time determined by the program arguments. 
*/
void	eat_sleep_think_routine(t_philo *philo)
{
	struct timeval	current_time;

	while (philo->data->finished == false)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		notify(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		notify(philo->data, philo->id, "has taken a fork");
		notify(philo->data, philo->id, "is eating");
		gettimeofday(&philo->last_meal, 0);
		philo->meals_eaten++;
		wait_sleep(philo->last_meal, philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		notify(philo->data, philo->id, "is sleeping");
		gettimeofday(&current_time, 0);
		wait_sleep(current_time, philo->data->time_to_sleep);
		notify(philo->data, philo->id, "is thinking");
	}
}

/*
Waits for the start_time then begins philosopher actions.
Even philosophers (who have an odd ID) start by thinking
to allow odd philosophers to grab forks. This avoids deadlocks
*/
void	*routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->last_meal = philo->data->start_time;
	while (elapsed_time(philo->data->start_time) < 0)
		continue ;
	if (philo->data->no_philos == 1)
		one_philo_routine(philo);
	else
	{
		if (philo->id % 2 != 0)
		{
			notify(philo->data, philo->id, "is thinking");
			usleep(10 * 1000);
		}
		eat_sleep_think_routine(philo);
	}
	return (NULL);
}
