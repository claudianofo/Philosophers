/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:28:03 by cnorton-          #+#    #+#             */
/*   Updated: 2024/03/06 17:28:16 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	correct_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (0);
	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j] && ft_isdigit(av[i][j]))
			j++;
		if (av[i][j] != '\0')
			return (0);
		j = 0;
		i++;
	}
	return (1);
}

int	correct_bounds(t_data *data)
{
	if (data->no_philo < 1 || data->no_philo > 200
		|| data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (0);
	return (1);
}

int	input_error(void)
{
	printf("input error\ncorrect input format:\n");
	printf("<no. philosphers> <time to die> <time to eat> ");
	printf("<time to sleep> <(optional)max no. meals>\n");
	printf("all inputs must be positive integers\n");
	printf("all times are in milliseconds (ms)\n");
	printf("inputs can't be zero (except max no. meals)\n");
	printf("no. philosophers can't exceed 200\n");
	return (1);
}