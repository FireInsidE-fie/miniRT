#ifndef AMBIENT_H
# define AMBIENT_H

# include "color.h"

typedef struct s_ambient
{
	double	intensity;	// Range [0, 1.0]
	t_color	color;	// RGB color
}	t_ambient;

void	create_ambient(double intensity, t_color color);

#endif // AMBIENT_H
