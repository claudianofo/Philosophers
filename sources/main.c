/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:43:20 by cnorton-          #+#    #+#             */
/*   Updated: 2024/05/02 12:30:25 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
prints the actions to stdout with a timestamp. A "write" mutex prevents multiple
threads from printing at the same time
*/
void	notify(t_data *data, int id, char *action)
{
	unsigned long int	elapsed_msec;

	if (data->finished == true)
		return ;
	pthread_mutex_lock(&data->write_mutex);
	elapsed_msec = elapsed_time(data->start_time);
	printf("%ld %d %s\n", elapsed_msec, id + 1, action);
	pthread_mutex_unlock(&data->write_mutex);
}

/*
Checks if either of the 2 end conditions have been  met:
If any philosophers have died (if they didn't eat within
the time_to_die timeframe)
OR if all philosophers have eaten at least the number of meals
specified by the optional 5th argument
*/
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

/*
Starts the simulation by setting a start-time (to sync the threads),
creating the philosopher threads and then calls the monitor function
from the main thread
*/
void	simulation(t_data *data, t_philo **philos)
{
	int				i;
	struct timeval	current_time;

	if (data->no_meals == 0)
		return ;
	i = 0;
	gettimeofday(&current_time, 0);
	data->start_time = make_future_timeval(current_time, 20 + data->no_philos);
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
	while (elapsed_time(data->start_time) < 0)
		continue ;
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
