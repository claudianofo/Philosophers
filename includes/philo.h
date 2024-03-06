/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorton- <cnorton-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:07:24 by cnorton-          #+#    #+#             */
/*   Updated: 2024/03/06 19:15:03 by cnorton-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include "structs.h"

//	input
int	input_error(void);
int	correct_bounds(t_data *data);
int	correct_args(int ac, char **av);

// utils
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif