#include "utils.h"
#include "libft.h"

#include <assert.h>
#include <stdbool.h>

/**
 * @brief Creates a new range element, representing all numbers between a
 * minimum and a maximum value.
 */
// TODO: remove such `new_element()` type of functions in favor of tmp elements
// like (t_range){min, max}
t_range	new_range(double min, double max)
{
	t_range	range;

	range.min = min;
	range.max = max;
	return (range);
}

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

float	ft_atof(char *str)
{
	float	result;
	float	decimal;

	assert(str && "String");
	result = ft_atoi(str);
	while (*str && (*str == '-' || ft_isdigit(*str)))
		++str;
	if (*str == '.')
	{
		decimal = ft_atoi(++str) / 10.0f;
		while (decimal >= 1.0f)				// Account for trailing 0s
			decimal /= 10;
		result += decimal;
	}
	// printf("[!] - atof got %f!\n", result);
	return (result);
}
