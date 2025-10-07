/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:38:28 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 13:53:00 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "parsing.h"

#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/**
 * @brief Converts a stringified number into a floating point representation.
 * Takes care of missing decimal parts, and accounts for trailing 0s.
 */

float	atof_return_decimal(char *str, float result, int sign)
{
	float	decimal;
	int		zeros;

	decimal = 0.0f;
	if (*str == '.' && ft_isdigit(*(str + 1)))
	{
		zeros = 0;
		while (*(++str) == '0')
			++zeros;
		if (!ft_isdigit(*str))
			return (result += decimal * sign);
		decimal = ft_atoi(str);
		while (decimal >= 1.0f || zeros-- > 0)
			decimal /= 10;
		result += decimal * sign;
	}
	return (result);
}

/**
 * @brief Converts a stringified number into a floating point representation.
 * Takes care of missing decimal parts, and accounts for trailing 0s.
 */
float	ft_atof(char *str)
{
	float	result;
	int		sign;

	while (*str == '0' && ft_isdigit(*(str + 1)))
		++str;
	result = ft_atoi(str);
	sign = 1;
	while (*str && (*str == '-' || ft_isdigit(*str)))
	{
		if (*(str++) == '-')
			sign = -1;
	}
	if (*str == '.' && ft_isdigit(*(str + 1)))
		result = atof_return_decimal(str, result, sign);
	return (result);
}
