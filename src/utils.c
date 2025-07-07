#include "utils.h"

#include <stdbool.h>

/**
 * @brief Creates a new range element, representing all numbers between a
 * minimum and a maximum value.
 */
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
