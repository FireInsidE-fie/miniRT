/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:42:28 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:42:29 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"
#include "minirt.h"
#include "point3.h"
#include "material.h"
#include "scene.h"
#include "vector.h"
#include "utils.h"
#include "cylinder.h"

#include <stdbool.h>
#include <math.h>

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
	return (color_mult(reflected, result->closest->mat.reflection));
}

t_vec3	reflect_ray(t_vec3 *ray, t_vec3 *normal)
{
	t_vec3	reflected;

	reflected = point3_scale(normal, 2 * dot_product(normal, ray));
	reflected = point3_sub(&reflected, ray);
	return (reflected);
}

float	get_specular_reflection(t_vec3 *point,
			t_vec3 *normal, t_vec3 *point_to_light, int specular)
{
	t_vec3	reflected;
	double	r_dot_v;
	t_vec3	view;

	view = point3_sub(&get_scene()->camera.position, point);
	reflected = reflect_ray(point_to_light, normal);
	r_dot_v = dot_product(&reflected, &view);
	if (r_dot_v > 0)
		return (
			pow(r_dot_v / (vec_len(&reflected) * vec_len(&view)), specular));
	return (0.0);
}
