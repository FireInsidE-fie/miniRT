#ifndef PLANE_H
# define PLANE_H

# include "point3.h"
# include "minirt.h"
# include "scene.h"
# include "vector.h"
# include <stdbool.h>

void	compute_plane_light(t_vec3 *normal, t_color *color, t_result *result);
void	handle_plane_intersect(double t[2], t_shape *tmp, t_range range, t_result *result);
int		create_plane(t_point3 position, t_vec3 normal, t_material mat);
bool	hit_plane(t_point3 *origin, t_vec3 *dir, t_shape *plane, double *t);

#endif
