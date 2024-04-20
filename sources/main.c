/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:43:20 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/20 15:06:41 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
Separate from the eat_sleep_think routine to avoid getting stuck
before grabbing the 2nd fork
*/
void	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	notify(philo->data, philo->id, "has taken a fork");
	return ;
}

void	eat_sleep_think_routine(t_philo *philo)
{
	while (philo->data->finished == false)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		notify(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mutex);
		notify(philo->data, philo->id, "has taken a fork");
		notify(philo->data, philo->id, "is eating");
		gettimeofday(&philo->last_meal, 0);
		philo->meals_eaten++;
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		notify(philo->data, philo->id, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
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
		continue;
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

void	monitor(t_data	*data)
{
	int		i;
	int		min_meals;

	data->finished = false;
	while (data->finished == false)
	{
		i = 0;
		min_meals = INT_MAX;
		while (i < data->no_philos)
		{
			if (elapsed_time(data->philos[i]->last_meal) >= data->time_to_die)
			{
				notify(data, i, "died");
				data->finished = true;
				return ;
			}
			if (data->no_meals > -1 && data->philos[i]->meals_eaten < min_meals)
				min_meals = data->philos[i]->meals_eaten;
			i++;
		}
		if (data->no_meals > -1 && min_meals >= data->no_meals)
			data->finished = true;
	}
	return ;
}

struct timeval	set_start_time(int no_philos)
{
	struct timeval	now;
	struct timeval	start_time;
	unsigned long int	incr_usec;

	gettimeofday(&now, 0);
	incr_usec = now.tv_usec + (no_philos + 20) * 1000;
	start_time.tv_usec = incr_usec % 1000000;
	start_time.tv_sec = incr_usec / 1000000 + now.tv_sec;
	return (start_time);
}

void	simulation(t_data *data, t_philo **philos)
{
	int	i;

	if (data->no_meals == 0)
		return ;
	i = 0;
	data->start_time = set_start_time(data->no_philos);
	while (i < data->no_philos)
	{
		if (pthread_create(&philos[i]->thread, NULL, &routine, philos[i]) != 0)
		{
			printf("error: pthread_create\n");
			join_threads(data, i);
			return (free_data(data, 3));
		}
		i++;
	}
	monitor(data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!correct_args(ac, av))
		return (input_error());
	data = init_data(av);
	if (!data)
		return (1);
	if (data->no_philos < 1 || data->no_philos > 200)
	{
		free_data(data, 1);
		return (input_error());
	}
	init_forks(data);
	if (!data)
		return (1);
	data->philos = init_philos(data);
	if (!data)
		return (1);
	simulation(data, data->philos);
	if (data)
		free_data(data, 4);
	return (0);
}
