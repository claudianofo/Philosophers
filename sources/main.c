/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:43:20 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/16 15:08:07 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	notify(struct timeval start_time, int id, char *action)
{
	struct timeval 		now;
	unsigned long int	elapsed_usec;

	gettimeofday(&now, 0);
	elapsed_usec = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) - ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
	printf("%ld %d %s\n", elapsed_usec, id, action);
}

void	*routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	for (int i = 0; i < 20; i++)
		notify(philo->data->start_time, philo->id, "is here");
	return (NULL);
}

void	begin(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	gettimeofday(&data->start_time, 0);
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
	init_forks(data);
	data->philos = init_philos(data);
	begin(data, data->philos);
	free(data);
}
