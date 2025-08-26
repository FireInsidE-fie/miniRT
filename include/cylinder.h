#ifndef CYLINDER_H
# define CYLINDER_H

# include "point3.h"
# include "minirt.h"
# include "scene.h"

# include <stdbool.h>

void	compute_cylinder_light(t_vec3 *normal, t_point3 *intersect,
	t_color *color, t_result *result);
t_vec3	get_cylinder_normal(t_shape *cyl, t_point3 *intersect);
void	handle_cylinder_intersect(double t[2], t_shape *cyl, t_range range, t_result *result);
bool	hit_cylinder(t_point3 *origin, t_vec3 *dir, t_shape *cyl, double *t);
void	print_cylinder(t_shape *cylinder);
void	create_cylinder(t_point3 *pos, t_vec3 *dir, float radius, float height, t_material *mat);

#endif
