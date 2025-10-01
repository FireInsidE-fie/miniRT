#include "scene.h"
#include "vector.h"
#include "minirt.h"

#include <math.h>

/**
 * @details
 * `base_to_p`: from cone->pos (tip) to intersect vector
 * `axis`: point reached within cone->direction from tip to dir scaled with m
 * `proj`: perpendicular with cone->dir, is placed where axis stops.
 * Has to get the proper incline applied on it in order to calculate the normal.
 * `m`: scalar used to determine how much base_to_p follows cone->direction
 */
t_vec3	get_cone_normal(t_shape *cone, t_point3 *intersect)
{
	t_vec3	base_to_p;
	t_vec3	axis;
	t_vec3	proj;
	t_vec3	normal;
	double	m;

	base_to_p = point3_sub(intersect, &cone->position);
	m = dot_product(&base_to_p, &cone->direction);
	axis = point3_scale(&cone->direction, m);
	proj = point3_sub(&base_to_p, &axis);
	proj = point3_scale(&proj, 1.0 / (pow((cone->radius / cone->height), 2)));
	normal = point3_add(&proj, &axis);
	vec_normalize(&normal);
	return (normal);
}

void	handle_cone_intersect(double t[2], t_shape *cone, t_result *result)
{
	if (t[0] >= 0 && t[0] < result->closest_t)
	{
		result->closest = cone;
		result->closest_t = t[0];
	}
	if (t[1] >= 0 && t[1] < result->closest_t)
	{
		result->closest = cone;
		result->closest_t = t[1];
	}
}

void	compute_cone_light(t_vec3 *normal, t_point3 *intersect,
	t_color *color, t_result *result)
{
	t_shape	*cone;

	cone = result->closest;
	*normal = get_cone_normal(cone, intersect);
	*color = cone->mat.color;
}
