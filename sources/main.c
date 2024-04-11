/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:43:20 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/09 17:21:58 by claudia          ###   ########.fr       */
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
		return (NULL);
	data->no_philos = ft_atoi(av[i++]);
	data->time_to_die = ft_atoi(av[i++]);
	data->time_to_eat = ft_atoi(av[i++]);
	data->time_to_sleep = ft_atoi(av[i++]);
	if (av[i])
		data->no_meals = ft_atoi(av[i]);
	else
		data->no_meals = -1;
	return (data);
}

t_philo	**init_philos(t_data *data)
{
	int	i;
	t_philo	**philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->no_philos); //I'm not sure if this is right
	if (!philos)//come back to malloc error handling 
		return (NULL);
	while (i < data->no_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		//if (!philos[i]) - handle
		philos[i]->data = data;
		philos[i]->id = i;
		i++;
	}
	return (philos);
}

void	*routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	printf("id = %d\n", philo->id);
	return (NULL);
}

void	start(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->no_philos)
	{
		if (pthread_create(&philos[i]->thread, NULL, &routine, philos[i]) != 0)
			printf("error occured\n");//handle error
		//printf("pthread_create returning %d\n", pthread_create(&philos[i]->thread, NULL, &routine, philos[i]));
		i++;
	}
	i = 0;
	while (i < data->no_philos)
	{
		pthread_join(philos[i]->thread, 0);
		i++;
	}
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
		return (input_error());
	data->philos = init_philos(data);
	start(data, data->philos);
	free(data);
}
