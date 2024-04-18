/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:13:34 by claudianofo       #+#    #+#             */
/*   Updated: 2024/04/19 00:44:50 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"

void    thread_error(t_data *data, int threads_created)
{
    int i;

    i = 0;
    while (i <= threads_created)
    {
        pthread_join(data->philos[i]->thread, 0);
		i++;
    }
    printf("error: pthread\n");
    return ;
}

void    *philo_error(t_data *data, int philos_created)
{
    int i;

    i = 0;
    printf("error: malloc\n");
    while (i <= philos_created)
    {
        free(data->philos[i]);
        i++;
    }
    free_data(data, data->no_philos, data->no_philos);
    return (NULL);
}

void    free_data(t_data *data, int forks_created, int fork_mutexes)
{
    int i;

    if (!data)
        return ;
    i = 0;
    while (i <= forks_created)
    {
        free(data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->write_mutex);
    i = 0;
    while (i <= fork_mutexes)
    {
        pthread_mutex_destroy(&data->forks[i]->mutex);
        i++;
    }
    if (data != NULL)
        free(data);
    return ;
}


