/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:43:20 by cnorton-          #+#    #+#             */
/*   Updated: 2024/03/05 17:22:33 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	correct_args(int ac,  char **av)
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

int	main(int ac, char **av)
{
	if (!correct_args(ac, av))
	{
		printf("input error\n");
		return (1);
	}
}