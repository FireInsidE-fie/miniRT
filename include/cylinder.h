#ifndef CYLINDER_H
# define CYLINDER_H

# include "point3.h"
# include "minirt.h"
# include "scene.h"
# include "vector.h"
# include <stdbool.h>

bool	hit_cylinder(t_point3 *origin, t_vec3 *dir, t_shape *cyl, double *t);
void	create_cylinder(t_point3 pos, t_vec3 dir, float radius, float height, t_material mat);

#endif
