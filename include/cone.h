#ifndef CONE_H
# define CONE_H

# include <stdbool.h>

# include "minirt.h"
# include "scene.h"

bool	hit_cone(t_point3 *origin, t_vec3 *dir, t_shape *cone, double *t);
int		create_cone(t_shape *tmp);
void	print_cone(t_shape *cone);

// Cone utils - cone_utils.c
t_vec3	get_cone_normal(t_shape *cone, t_point3 *intersect);
void	handle_cone_intersect(double t[2], t_shape *cone, t_result *result);
void	compute_cone_light(t_vec3 *normal, t_point3 *intersect,
			t_color *color, t_result *result);

#endif
