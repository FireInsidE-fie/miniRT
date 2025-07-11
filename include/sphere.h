#ifndef SPHERE_H
# define SPHERE_H

# include "scene.h"
# include "point3.h"
# include "color.h"

# include <stdbool.h>

// Representation of a sphere in 3D space //
typedef struct s_sphere
{
	t_point3		center;
	float			radius;
	t_color			color;
	int				specular;
	struct s_sphere	*next;
}	t_sphere;

// Functions //
int		create_sphere(t_point3 position, float radius, t_color color);
void	print_sphere(t_shape *sphere);
bool	hit_sphere(t_point3 *origin, t_vec3 *dir, t_shape *sphere, double *t);

#endif // SPHERE_H
