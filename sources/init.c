/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:29:08 by claudianofo       #+#    #+#             */
/*   Updated: 2024/05/02 10:42:18 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
Allocates memory for the main data struct, and saves the arg paramaters
to the struct. Mutexes and some other variables are also initialised
*/
t_data	*init_data(char **av)
{
	t_data	*data;
	int		i;

	i = 1;
	data = malloc(sizeof(t_data));
	if (!data)
		printf("error: malloc\n");
	if (!data)
		return (NULL);
	data->finished = false;
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

/*
Called if there is a malloc or mutex error during fork initialisation.
The number of succesfuly initialised mallocs and mutexes are sent to
the free_forks function for cleanup
*/
void	fork_error(char *type, t_data *data, int malloc, int mutex)
{
	printf("error: %s\n", type);
	free_forks(data, malloc, mutex);
	return (free_data(data, 1));
}

/*
Allocates memory for the array of fork structs and the individual structs,
and initialises one mutex for every fork
*/
void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_fork) * data->no_philos);
	if (data->forks == NULL)
	{
		printf("error: malloc\n");
		return (free_data(data, 1));
	}
	i = 0;
	while (i < data->no_philos)
	{
		data->forks[i] = malloc(sizeof(t_fork));
		if (data->forks[i] == NULL)
			return (fork_error("malloc", data, i, i));
		data->forks[i]->id = i;
		if (pthread_mutex_init(&data->forks[i]->mutex, NULL) != 0)
			return (fork_error("mutex", data, i + 1, i));
		i++;
	}
}

/*
Initialises the data in a philo struct, and allocates the left and right forks
*/
void	init_philo_data(t_data *data, t_philo *philo, int i, t_fork **forks)
{
	philo->data = data;
	philo->id = i;
	philo->meals_eaten = 0;
	if (i == 0)
		philo->left_fork = forks[data->no_philos - 1];
	else
		philo->left_fork = forks[i - 1];
	philo->right_fork = forks[i];
}

/*
Allocates memory for the array of philo structs and the individual structs
*/
t_philo	**init_philos(t_data *data)
{
	int		i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->no_philos);
	if (!philos)
	{
		printf("error: malloc\n");
		free_data(data, 2);
		return (NULL);
	}
	while (i < data->no_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			printf("error: malloc\n");
			free_philos(data, i);
			free_data(data, 2);
			return (NULL);
		}
		init_philo_data(data, philos[i], i, data->forks);
		i++;
	}
	return (philos);
}
