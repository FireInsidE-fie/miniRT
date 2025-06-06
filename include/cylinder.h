#ifndef CYLINDER_H
# define CYLINDER_H

# include "minirt.h"
# include "color.h"

typedef struct s_cylinder
{
	t_point3	center;
	t_vector3	axis;
	double		radius;
	double		height;
	t_color		color;
}	t_cylinder;

#endif // CYLINDER_H
