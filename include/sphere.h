#ifndef SPHERE_H
# define SPHERE_H

# include "minirt.h"
# include "scene.h"
# include "point3.h"
# include "material.h"

# include <stdbool.h>

// Functions //
int		create_sphere(t_point3 *position, float radius, t_material *mat);
void	compute_sphere_light(t_vec3 *normal,
			t_point3 *intersect,
			t_color *color,
			t_result *result);
void	handle_sphere_intersect(double t[2], t_shape *tmp, t_result *result);
void	print_sphere(t_shape *sphere);
bool	hit_sphere(t_point3 *origin, t_vec3 *dir, t_shape *sphere, double *t);

t_color	get_checker_color(t_shape *sphere, t_point3 *point);

#endif // SPHERE_H
