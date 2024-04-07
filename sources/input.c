/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:28:03 by cnorton-          #+#    #+#             */
/*   Updated: 2024/04/01 16:22:11 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	correct_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (false);
	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j] && ft_isdigit(av[i][j]))
			j++;
		if (av[i][j] != '\0')
			return (false);
		j = 0;
		i++;
	}
	return (true);
}

int	input_error(void)
{
	printf("input error\ncorrect input format:\n");
	printf("<no. of philosphers> <time to die> <time to eat> ");
	printf("<time to sleep> <(optional)max no. meals>\n");
	printf("all inputs must be positive integers or zero\n");
	printf("all times are in milliseconds (ms)\n");
	printf("no. of philosophers must be between 1 and 200, inclusively\n");
	return (1);
}