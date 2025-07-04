#ifndef UTILS_H
# define UTILS_H

// Represents a range between two values.
typedef struct s_range {
	double	min;
	double	max;
}	t_range;

t_range	new_range(double min, double max);
double	clamp(double x, t_range range);

#endif // UTILS_H
