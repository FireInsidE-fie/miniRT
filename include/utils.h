/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:48 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:20:59 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parsing.h"

# include <stdbool.h>

typedef struct s_color	t_color;

// Represents a range between two values.
typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

bool	is_in_range(double x, t_range range);
double	clamp(double x, t_range range);
bool	check_path(char *path);
t_ps	check_number(char *str);
float	ft_atof(char *str);

#endif // UTILS_H
