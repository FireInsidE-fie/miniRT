#ifndef CYLINDER_H
# define CYLINDER_H

# include "point3.h"
# include "material.h"

typedef struct s_cylinder
{
	t_point3			center;
	t_vec3				axis;
	float				radius;
	float				height;
	t_material			mat;
	struct s_cylinder	*next;
}	t_cylinder;

#endif // CYLINDER_H
