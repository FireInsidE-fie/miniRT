#ifndef SPHERE_H
# define SPHERE_H

# include "point3.h"
# include "color.h"

# include <stdbool.h>

// Representation of a sphere in 3D space //
typedef struct s_sphere
{
	t_point3		center;
	double			radius;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

// Functions //
int		create_sphere(t_point3 position, double radius, t_color color);
void	print_sphere(t_sphere *sphere);
bool	hit_sphere(t_point3 origin, t_vec3 dir, t_sphere *sphere, double *t);

#endif // SPHERE_H
