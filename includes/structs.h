/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:04:24 by cnorton-          #+#    #+#             */
/*   Updated: 2024/03/25 14:47:10 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	int	no_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	no_meals;
}		t_data;

//typedef struct s_philo;

#endif