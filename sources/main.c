/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:43:20 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/18 22:20:00 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_elapsed_time(struct timeval start_time)
{
	struct timeval 		now;
	unsigned long int	elapsed_millisec;

	gettimeofday(&now, 0);
	elapsed_millisec = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) - ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
	return (elapsed_millisec);
}

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

void	*routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->last_meal = philo->data->start_time;
	if (philo->id % 2 != 0)
	{
		notify(philo->data, philo->id, "is thinking");
		wait_sleep(10); //revisit this
	}
	while (philo->data->finished == false)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		notify(philo->data, philo->id, "has taken a fork");
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
	return (NULL);
}

void	*monitor(void *data_arg)
{
	t_data	*data;
	int		i;
	int		least_meals_eaten;

	data = (t_data *)data_arg;
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
				break;
			}
			if (data->no_meals > -1 && data->philos[i]->meals_eaten < least_meals_eaten)
				least_meals_eaten = data->philos[i]->meals_eaten;
			i++;
		}
		if (data->no_meals > -1 && least_meals_eaten >= data->no_meals)
			data->finished = true;
	}
	return (NULL);
}

void	begin(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	gettimeofday(&data->start_time, 0);//should start_time be initialised after all threads created?
	while (i < data->no_philos)
	{
		if (pthread_create(&philos[i]->thread, NULL, &routine, philos[i]) != 0)
			printf("error occured\n");//handle error
		//printf("pthread_create returning %d\n", pthread_create(&philos[i]->thread, NULL, &routine, philos[i]));
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, &monitor, data);
	i = 0;
	while (i < data->no_philos)
	{
		pthread_join(philos[i]->thread, 0);
		i++;
	}
	pthread_join(data->monitor_thread, 0);
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
	init_forks(data);
	data->philos = init_philos(data);
	begin(data, data->philos);
	free(data);
}
