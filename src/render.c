#include "minirt.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"
#include "cone.h"
#include "utils.h"
#include "material.h"
#include "mlx.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// Reflection Depth, going over 3 barely adds anything visually
#define MAXDEPTH 3

/**
 * @brief Computes the closest intersection between a ray starting at `origin`
 * in direction `dir`, contained within `range`.
 * Skips the origin.shape shape if it exists, which means the ray started from
 * a shape and must then exclude this shape (to fix acne in shadows
 * and reflections).
 *
 * @return A `t_result` struct containing a pointer to the sphere intersected
 * and the t value at that point.
 */
t_result	closest_intersect(t_origin origin, t_vec3 *dir)
{
	t_shape		*s;
	t_result	result;
	double		t[2];

	result.closest = NULL;
	result.closest_t = INFINITY;
	s = get_scene()->shapes;
	while (s)
	{
		if (s == origin.shape)
			;
		else if (s->type == SPHERE && hit_sphere(origin.point, dir, s, t))
			handle_sphere_intersect(t, s, &result);
		else if (s->type == PLANE && hit_plane(origin.point, dir, s, t))
			handle_plane_intersect(t, s, &result);
		else if (s->type == CYLINDER && hit_cylinder(origin.point, dir, s, t))
			handle_cylinder_intersect(t, s, &result);
		else if (s->type == CONE && hit_cone(origin.point, dir, s, t))
			handle_cone_intersect(t, s, &result);
		s = s->next;
	}
	return (result);
}

/**
 * @brief Checks the lightning for a point of a shape and computes that point's
 * color with the lightning on top.
 * @details Uses the `t_result` struct to know the `t` value and the intersected
 * sphere's color.
 */
static t_color	compute_light(t_point3 *origin, t_vec3 *dir, t_result *result)
{
	t_point3	intersect;
	t_vec3		normal;
	t_color		color;
	t_color		intensity;

	intersect = *origin;
	intersect.x += dir->x * result->closest_t;
	intersect.y += dir->y * result->closest_t;
	intersect.z += dir->z * result->closest_t;
	if (result->closest->type == SPHERE)
		compute_sphere_light(&normal, &intersect, &color, result);
	else if (result->closest->type == PLANE)
		compute_plane_light(&normal, &intersect, &color, result);
	else if (result->closest->type == CYLINDER)
		compute_cylinder_light(&normal, &intersect, &color, result);
	else if (result->closest->type == CONE)
		compute_cone_light(&normal, &intersect, &color, result);
	intensity = get_light_intensity(
			(t_origin){&intersect, result->closest},
			&normal, result->closest->mat.specular);
	color.r *= clamp(intensity.r, (t_range){0.0f, 1.0f});
	color.g *= clamp(intensity.g, (t_range){0.0f, 1.0f});
	color.b *= clamp(intensity.b, (t_range){0.0f, 1.0f});
	return (color);
}

/**
 * @brief Finds the closest object to the `origin` on a ray with `direction`,
 * and returns its color.
 */
t_color	ray_color(t_point3 origin, t_shape *self, t_vec3 dir, int depth)
{
	t_result	result;
	t_color		local_color;
	t_color		reflected;

	result = closest_intersect((t_origin){&origin, self}, &dir);
	if (!result.closest)
		return ((t_color){SKY_COLOR, SKY_COLOR, SKY_COLOR});
	local_color = compute_light(&origin, &dir, &result);
	if (depth <= 0 || result.closest->mat.reflection <= 0.0f)
		return (local_color);
	reflected = compute_reflection(
			(t_origin){&origin, result.closest}, &dir, &result, depth);
	return (color_add(color_mult(
				local_color, 1 - result.closest->mat.reflection), reflected));
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
			NULL,
			camera_apply_rotation(
				camera_to_viewport(get_core()->render.x, get_core()->render.y),
				&get_scene()->camera), MAXDEPTH
			);
	img_put_pixel(&get_core()->img,
		get_core()->render.x + WIN_WIDTH / 2,
		get_core()->render.y + WIN_HEIGHT / 2,
		color_to_int(&color));
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
