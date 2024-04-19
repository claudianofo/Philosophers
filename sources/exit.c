/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:13:34 by claudianofo       #+#    #+#             */
/*   Updated: 2024/04/19 15:30:46 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    join_threads(t_data *data, int threads_created)
{
    int i;

    i = 0;
    while (i < threads_created)
    {
        pthread_join(data->philos[i]->thread, 0);
		i++;
    }
}

void    free_philos(t_data *data, int philos_created)
{
    int i;

    i = 0;
    while (i < philos_created)
    {
        free(data->philos[i]);
        i++;
    }
    free(data->philos);
}

/*
destorys mutexes and frees allocated memory for forks
*/
void    free_forks(t_data *data, int forks_created, int fork_mutexes)
{
    int i;

    i = 0;
    while (i < fork_mutexes)
    {
        pthread_mutex_destroy(&data->forks[i]->mutex);
        i++;
    }
    i = 0;
    while (i < forks_created)
    {
        free(data->forks[i]);
        i++;
    }
    free(data->forks);
}

/*
This function is used for cleanup if an error occurs, or upon completion of simulation
Cleanup codes:
1 = destory write mutex only and free data only
2 = free all memory except philos, destory all mutexes
3 = free all memory, destory all mutexes
4 = free all memory, destory all mutexes and join threads
*/
void    free_data(t_data *data, int cleanup_code)
{
    if (!data)
        return ;
    pthread_mutex_destroy(&data->write_mutex);
    if (cleanup_code == 4)
        join_threads(data, data->no_philos);
    if (cleanup_code >= 3)
        free_philos(data, data->no_philos);
    if (cleanup_code >= 2)
        free_forks(data, data->no_philos, data->no_philos);    
    free(data);
}


