/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:36:10 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/26 15:37:16 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

struct timeval	make_future_timeval(struct timeval start, int wait_time)
{
	struct timeval		goal_time;
	unsigned long int	incr_usec;

	incr_usec = start.tv_usec + wait_time * 1000;
	goal_time.tv_usec = incr_usec % 1000000;
	goal_time.tv_sec = incr_usec / 1000000 + start.tv_sec;
	return (goal_time);
}

void	wait_sleep(struct timeval start, int wait_time)
{
	struct timeval	goal_time;

	goal_time = make_future_timeval(start, wait_time);
	while (elapsed_time(goal_time) < -35)
		usleep(30 * 1000);
	while (elapsed_time(goal_time) < 0)
		continue ;
	return ;
}

int	elapsed_time(struct timeval goal_time)
{
	struct timeval		now;
	unsigned long int	elapsed_msec;

	gettimeofday(&now, 0);
	elapsed_msec = ((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((goal_time.tv_sec * 1000) + (goal_time.tv_usec / 1000));
	return (elapsed_msec);
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
