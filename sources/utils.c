/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:36:10 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/19 16:48:33 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	notify(t_data *data, int id, char *action)
{
	unsigned long int	elapsed_millisec;

	if (data->finished == true)
		return ;
	elapsed_millisec = elapsed_time(data->start_time);
	pthread_mutex_lock(&data->write_mutex);
	printf("%ld %d %s\n", elapsed_millisec, id + 1, action);
	pthread_mutex_unlock(&data->write_mutex);
}

void	wait_sleep(int millisec)
{
	usleep(millisec * 1000);
}

int	elapsed_time(struct timeval start_time)
{
	struct timeval		now;
	unsigned long int	elapsed_millisec;

	gettimeofday(&now, 0);
	elapsed_millisec = ((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
	return (elapsed_millisec);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
