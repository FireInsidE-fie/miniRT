#include "light.h"
#include "minirt.h"
#include "point3.h"
#include "material.h"
#include "scene.h"
#include "vector.h"
#include "utils.h"
#include "cylinder.h"

#include <stdbool.h>
#include <assert.h>

/**
 * @brief Multiplies a color by a given factor.
 */
// TODO: should probably be called `color_mult`
t_color	scale_color(t_color c, float factor)
{
	t_range	range;
	t_color	result;

	range = (t_range){0.0, 1.0};
	result.r = clamp(c.r * factor, range);
	result.g = clamp(c.g * factor, range);
	result.b = clamp(c.b * factor, range);
	return (result);
}

t_color	add_color(t_color a, t_color b)
{
	t_range	range;
	t_color	result;

	range = (t_range){0.0, 1.0};
	result.r = clamp(a.r + b.r, range);
	result.g = clamp(a.g + b.g, range);
	result.b = clamp(a.b + b.b, range);
	return (result);
}

static t_point3	get_intersection_point(t_point3 *origin, t_vec3 *dir, float t)
{
	t_vec3	offset;

	offset = point3_scale(dir, t);
	return (point3_add(origin, &offset));
}

static t_vec3	get_normal(t_result *result, t_point3 *point)
{
	t_vec3	normal;

	if (result->closest->type == SPHERE)
	{
		normal = point3_sub(point, &result->closest->position);
		vec_normalize(&normal);
	}
	else if (result->closest->type == PLANE)
		normal = result->closest->normal;
	else
		normal = get_cylinder_normal(result->closest, point);
	return (normal);
}

/**
 * @brief Recursive function that is called when a ray has to bounce off of a
 * mirrory surface, up to `depth` times.
 * @details
 * Once `depth` reaches 0, the recursive stops.
 * This is actually a recursive function in two steps; first ray_color
 * is called, then this function, then ray color again,
 * until `depth` reaches 0 (or we reach a non-reflective surface.)
 */
t_color	compute_reflection(t_origin origin, t_vec3 *dir, t_result *result,
		int depth)
{
	t_point3	intersect;
	t_vec3		normal;
	t_vec3		view_dir;
	t_vec3		reflected_dir;
	t_color		reflected;

	intersect = get_intersection_point(origin.point, dir, result->closest_t);
	normal = get_normal(result, &intersect);
	view_dir = point3_scale(dir, -1);
	reflected_dir = reflect_ray(&view_dir, &normal);
	if (depth <= 0 || result->closest->mat.reflection <= 0.0f)
		return ((t_color){0, 0, 0});
	reflected = ray_color(intersect, origin.shape, reflected_dir, depth - 1);
	return (scale_color(reflected, result->closest->mat.reflection));
}
