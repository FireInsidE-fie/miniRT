#ifndef LIGHT_H
# define LIGHT_H

# include "minirt.h"
# include "color.h"

typedef struct s_light
{
	t_point3	position;
	double		ratio;	// Range [0, 1.0]
	t_color		color;	// RGB color
}	t_light;

#endif // LIGHT_H
