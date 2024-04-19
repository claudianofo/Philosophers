/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:36:10 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/19 15:03:45 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
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

void	wait_sleep(int millisec)
{
	usleep(millisec * 1000);
}

int	get_elapsed_time(struct timeval start_time)
{
	struct timeval 		now;
	unsigned long int	elapsed_millisec;

	gettimeofday(&now, 0);
	elapsed_millisec = ((now.tv_sec * 1000) + (now.tv_usec / 1000)) - ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
	return (elapsed_millisec);
}