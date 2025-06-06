#ifndef PLANE_H
# define PLANE_H

# include "vector.h"
# include "color.h"

typedef struct s_plane
{
	t_point3	center;
	t_vec3		normal;
	t_color		color;
}	t_plane;

#endif // PLANE_H
