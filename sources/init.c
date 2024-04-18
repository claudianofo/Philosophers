/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:29:08 by claudianofo       #+#    #+#             */
/*   Updated: 2024/04/19 00:46:05 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_data	*init_data(char **av)
{
	t_data	*data;
	int		i;

	i = 1;
	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("error: malloc\n");
		return (NULL);
	}
	data->no_philos = ft_atoi(av[i++]);
	data->time_to_die = ft_atoi(av[i++]);
	data->time_to_eat = ft_atoi(av[i++]);
	data->time_to_sleep = ft_atoi(av[i++]);
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
	{
		printf("error: mutex\n");
		free(data);
		return (NULL);
	}
	if (av[i])
		data->no_meals = ft_atoi(av[i]);
	else
		data->no_meals = -1;
	return (data);
}

void	assign_forks(t_philo *philo, int i, t_fork **forks, int no_philos)
{
	if (i == 0)
		philo->left_fork = forks[no_philos - 1];
	else 
		philo->left_fork = forks[i - 1];
	philo->right_fork = forks[i];
}

t_philo	**init_philos(t_data *data)
{
	int	i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->no_philos);
	if (!philos)
	{
		printf("error: malloc\n");
		free_data(data, data->no_philos, data->no_philos);
		return (NULL);
	}
	while (i < data->no_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (philo_error(data, i - 1));
		philos[i]->data = data;
		philos[i]->id = i;
		philos[i]->meals_eaten = 0;
		assign_forks(philos[i], i, data->forks, data->no_philos);
		i++;
	}
	return (philos);
}

void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->no_philos);
	if (data->forks == NULL)
	{	
		printf("error: malloc\n");
		return (free_data(data, 0, 0));
	}
	i = 0;
	while (i < data->no_philos)
	{
		data->forks[i] = malloc(sizeof(t_fork));
		if (data->forks[i] == NULL)
		{	
			printf("error: malloc\n");
			return (free_data(data, i - 1, i - 1));
		}
		data->forks[i]->id = i;
		if (pthread_mutex_init(&data->forks[i]->mutex, NULL) != 0)
		{
			printf("error: malloc\n");
			return (free_data(data, i, i - 1));
		}
		i++;
	}
}
