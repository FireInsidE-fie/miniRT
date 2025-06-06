#ifndef SPHERE_H
# define SPHERE_H

# include "color.h"
# include "vector.h"

// Representation of a sphere in 3D space //
typedef struct s_sphere
{
	t_point3		center;
	double			radius;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

#endif // SPHERE_H
