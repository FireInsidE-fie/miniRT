#include "camera.h"
#include "light.h"
#include "minirt.h"
#include "point3.h"
#include "material.h"
#include "scene.h"
#include "sphere.h"
#include "math.h"
#include "mlx.h"
#include "vector.h"
#include "utils.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief Computes the closest intersection between a ray starting at `origin`
 * in direction `dir`, contained within `range`.
 *
 * @return A `t_result` struct containing a pointer to the sphere intersected
 * and the t value at that point.
 */
t_result	closest_intersect(t_point3 *origin, t_vec3 *dir, t_range range)
{
	t_shape		*tmp;
	t_result	result;
	double		t[2];

	assert("Origin" && origin);
	assert("Direction" && dir);
	assert("Range" && range.min >= 0.0 && range.max >= range.min);
	result.closest = NULL;
	result.closest_t = range.max;
	tmp = get_scene()->shapes;
	while (tmp)
	{
		if (hit_sphere(origin, dir, tmp, t))
		{
			if (is_in_range(t[0], range) && t[0] < result.closest_t)
			{
				result.closest = tmp;
				result.closest_t = t[0];
			}
			if (is_in_range(t[1], range) && t[1] < result.closest_t)
			{
				result.closest = tmp;
				result.closest_t = t[1];
			}
		}
		tmp = tmp->next;
	}
	return (result);
}

/**
 * @brief Checks the (for now) diffuse lightning for a point of a (for now)
 * sphere, and computes that point's color with the lightning on top.
 * @details Uses the `t_result` struct to know the `t` value and the intersected
 * sphere's color.
 */
static t_color	compute_light(
	t_point3 *origin,
	t_vec3 *dir,
	t_result *result,
	int depth)
{
	t_point3	intersect;
	t_vec3		normal;
	t_color		color;
	float		intensity;

	assert("Origin" && origin);
	assert("Direction" && dir);
	assert("Closest" && result->closest);
	assert("Closest_t" && result->closest_t >= 0.0);
	intersect = *origin;
	intersect.x += dir->x * result->closest_t;
	intersect.y += dir->y * result->closest_t;
	intersect.z += dir->z * result->closest_t;
	normal = point3_sub(&intersect, &result->closest->position);
	vec_normalize(&normal);
	color = result->closest->mat.color;
	intensity = clamp(
			get_light_intensity(&intersect, &normal, result->closest->mat.specular),
			new_range(0.0, 1.0));
	color.r *= intensity;
	color.g *= intensity;
	color.b *= intensity;
	if (depth <= 0 || result->closest->mat.reflection <= 0.0)
		return (color);

	// Recursive ray tracing ===================================================

	float	r_ratio = result->closest->mat.reflection;
	t_vec3	reflected = point3_invert(dir);
	reflected = reflect_ray(&reflected, &normal);
	t_color	reflected_color = ray_color(*origin, *dir, new_range(0.001, INFINITY), depth - 1);
	color.r = color.r * (1 - r_ratio) + reflected_color.r * r_ratio;
	color.g = color.g * (1 - r_ratio) + reflected_color.g * r_ratio;
	color.b = color.b * (1 - r_ratio) + reflected_color.b * r_ratio;
	return (color);
}

/**
 * @brief Finds the closest object to the `origin` on a ray with `direction`,
 * and returns its color.
 */
t_color	ray_color(t_point3 origin, t_vec3 dir, t_range t_range, int depth)
{
	t_result	result;

	result = closest_intersect(&origin, &dir, t_range);
	if (result.closest)
		return (compute_light(&origin, &dir, &result, depth));
	return ((t_color)SKY_COLOR);
}

/**
 * @brief Gets called inside the double while statement of the render loop.
 * Prints each pixel for each blocks.
 */
static void	process_bloc_render(void)
{
	t_color	color;

	color = ray_color(
			get_scene()->camera.position,
			camera_to_viewport(get_core()->render.x, get_core()->render.y),
			new_range(0.001, INFINITY),
			RECURSION_DEPTH
		);
	img_put_pixel(&get_core()->img,
		get_core()->render.x + WIN_WIDTH / 2,
		get_core()->render.y + WIN_HEIGHT / 2,
		&color);
	get_core()->render.x++;
}

/**
 * @brief The "Pretty" render loop.
 * Used so we can interact with mlx while rendering.
 */
int	render(void *param)
{
	int	i;
	int	j;

	(void)param;
	if (get_core()->render.y > WIN_HEIGHT / 2)
	{
		get_core()->render.is_rendering = 0;
		return (0);
	}
	j = 0;
	while (j < BLOCK_SIZE && get_core()->render.y <= WIN_HEIGHT / 2)
	{
		i = 0;
		while (i++ < BLOCK_SIZE && get_core()->render.x <= WIN_WIDTH / 2)
			process_bloc_render();
		if (get_core()->render.x > WIN_WIDTH / 2)
		{
			get_core()->render.x = -WIN_WIDTH / 2;
			get_core()->render.y++;
		}
		j++;
	}
	mlx_put_image_to_window(
		get_core()->mlx, get_core()->win, get_core()->img.img, 0, 0);
	return (0);
}
