#ifndef PLANE_H
# define PLANE_H

# include "point3.h"
# include "material.h"

typedef struct s_plane
{
	t_point3		center;
	t_vec3			normal;
	t_material		mat;
	struct s_plane	*next;
}	t_plane;

#endif // PLANE_H
