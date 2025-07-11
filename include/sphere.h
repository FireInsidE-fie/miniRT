#ifndef SPHERE_H
# define SPHERE_H

# include "scene.h"
# include "point3.h"
# include "material.h"

# include <stdbool.h>

// Functions //
int		create_sphere(t_point3 position, float radius, t_material mat);
void	print_sphere(t_shape *sphere);
bool	hit_sphere(t_point3 *origin, t_vec3 *dir, t_shape *sphere, double *t);

#endif // SPHERE_H
