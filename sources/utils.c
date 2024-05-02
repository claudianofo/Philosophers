/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudianofo <claudianofo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:36:10 by cnorton-          #+#    #+#             */
/*   Updated: 2024/05/02 12:26:21 by claudianofo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*
Returns a timeval struct (same data type that is returned by gettimeofday())
that is wait_time milliseconds in the future
*/
struct timeval	make_future_timeval(struct timeval start, int wait_time)
{
	struct timeval		target_time;
	unsigned long int	incr_usec;

	incr_usec = start.tv_usec + wait_time * 1000;
	target_time.tv_usec = incr_usec % 1000000;
	target_time.tv_sec = incr_usec / 1000000 + start.tv_sec;
	return (target_time);
}

/*
Alternates between usleep() for 30 milliseconds and checking if
the current time is within 35 milliseconds of the target time.
This is necessary because usleep waits for inaccurate lengths of time,
especially on macOS
*/
void	wait_sleep(struct timeval start, int wait_time)
{
	struct timeval	target_time;

	target_time = make_future_timeval(start, wait_time);
	while (elapsed_time(target_time) < -35)
		usleep(30 * 1000);
	while (elapsed_time(target_time) < 0)
		continue ;
	return ;
}

/*
Calculates and returns the difference in milliseconds between the 
current time and target time. Result can be positive or negative
*/
int	elapsed_time(struct timeval target_time)
{
	struct timeval		now;
	unsigned long int	elapsed_msec;

	gettimeofday(&now, 0);
	elapsed_msec = ((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((target_time.tv_sec * 1000) + (target_time.tv_usec / 1000));
	return (elapsed_msec);
}

/*
Converts strings of numbers to integers
*/
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

/*
Checks that a character is a number between 0 and 9
*/
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
