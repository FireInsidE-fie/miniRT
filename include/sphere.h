#ifndef SPHERE_H
# define SPHERE_H

# include "color.h"
# include "minirt.h"

// Representation of a sphere in 3D space //
typedef struct s_sphere
{
	t_point3	center;
	double		radius;
	t_color		color;
}	t_sphere;

#endif // SPHERE_H
