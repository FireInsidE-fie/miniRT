/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:23:59 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:25:00 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "parsing.h"

#include <stdint.h>
#include <stdbool.h>

bool	is_in_range(double x, t_range range)
{
	return (x >= range.min && x <= range.max);
}

/**
 * @brief Clamps a value between the `min` and `max` values.
 */
double	clamp(double x, t_range range)
{
	if (x < range.min)
		return (range.min);
	else if (x > range.max)
		return (range.max);
	return (x);
}

/**
 * @brief Checks if a given string ends in .rt (pre-checks before parsing).
 * @return true if path is a .rt file, false otherwise.
 */
bool	check_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		++i;
	if (i <= 3)
		return (false);
	if (ft_strncmp(path + i - 3, ".rt", 3) != 0)
		return (false);
	return (true);
}

/**
 * @brief Checks the number found at `str` for integrity.
 * By that we mean one or multiple `+` or `-` signs, followed by numbers, then
 * either a comma `,`, a point `.`, a space ` ` or a line break '\n'.
 * If anything else follows the numbers, a wrong character error is returned.
 */
t_ps	check_number(char *str)
{
	if (!*str || (!ft_isdigit(*str) && *str != '-' && *str != '+'))
		return (CHAR_ERR);
	while (*str && (*str == '-' || *str == '+'))
		++str;
	if (!ft_isdigit(*str))
		return (CHAR_ERR);
	while (ft_isdigit(*str))
		++str;
	if (*str && *str != '\n' && *str != ',' && *str != '.'
		&& ft_isprint(*str) && *str != ' ')
		return (CHAR_ERR);
	return (DONE);
}
