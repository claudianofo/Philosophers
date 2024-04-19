/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:43:20 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/19 15:03:33 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	notify(t_data *data, int id, char *action)
{
	unsigned long int	elapsed_millisec;

	if (data->finished == true)
		return ;
	elapsed_millisec = get_elapsed_time(data->start_time);
	pthread_mutex_lock(&data->write_mutex);
	printf("%ld %d %s\n", elapsed_millisec, id + 1, action);
	pthread_mutex_unlock(&data->write_mutex);
}

void	eat_sleep_think(t_philo *philo)
{
	while (philo->data->finished == false)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		notify(philo->data, philo->id, "has taken a fork");
		if (philo->data->no_philos == 1)
			return ;
		pthread_mutex_lock(&philo->right_fork->mutex);
		notify(philo->data, philo->id, "has taken a fork");
		notify(philo->data, philo->id, "is eating");
		gettimeofday(&philo->last_meal, 0);
		philo->meals_eaten++;
		wait_sleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		notify(philo->data, philo->id, "is sleeping");
		wait_sleep(philo->data->time_to_sleep);
		notify(philo->data, philo->id, "is thinking");
	}
}

void	*routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->last_meal = philo->data->start_time;
	if (philo->id % 2 != 0)
	{
		notify(philo->data, philo->id, "is thinking");
		wait_sleep(10);
	}
	eat_sleep_think(philo);
	return (NULL);
}

void	monitor(t_data	*data)
{
	int		i;
	int		least_meals_eaten;

	data->finished = false;
	while (data->finished == false)
	{
		i = 0;
		least_meals_eaten = INT_MAX;
		while (i < data->no_philos)
		{
			if (get_elapsed_time(data->philos[i]->last_meal) >= data->time_to_die)
			{
				notify(data, i, "died");
				data->finished = true;
				return;
			}
			if (data->no_meals > -1 && data->philos[i]->meals_eaten < least_meals_eaten)
				least_meals_eaten = data->philos[i]->meals_eaten;
			i++;
		}
		if (data->no_meals > -1 && least_meals_eaten >= data->no_meals)
			data->finished = true;
	}
	return ;
}

void	simulation(t_data *data, t_philo **philos)
{
	int	i;

	if (data->no_meals == 0)
		return ;
	i = 0;
	gettimeofday(&data->start_time, 0);
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
