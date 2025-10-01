#ifndef UTILS_H
# define UTILS_H

# include "minirt.h"

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
float	ft_atof(char *str);
void	img_put_pixel(t_img *img, int x, int y, int color);

#endif // UTILS_H
