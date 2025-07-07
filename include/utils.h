#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

// Represents a range between two values.
typedef struct s_range {
	double	min;
	double	max;
}	t_range;

t_range	new_range(double min, double max);
bool	is_in_range(double x, t_range range);
double	clamp(double x, t_range range);

#endif // UTILS_H
