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
#include "plane.h"
#include "cylinder.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#define MAXDEPTH 3

/* TODO feel free to rearrange things, add static statements because the following functions were made
	for norm and readability purposes. but they're just part of compute_light()
*/

t_vec3	get_cylinder_normal(t_shape *cyl, t_point3 *intersect)
{
	t_vec3		base_to_p;
	t_vec3		proj;
	t_vec3		normal;
	double		axis_height;

	base_to_p = point3_sub(intersect, &cyl->position);
	axis_height = dot_product(&base_to_p, &cyl->direction);
	proj = point3_scale(&cyl->direction, axis_height);
	normal = point3_sub(&base_to_p, &proj);
	vec_normalize(&normal);
	return (normal);
}

void	compute_sphere_light(t_vec3 *normal, t_point3 *intersect, t_color *color, t_result *result)
{
	*normal = point3_sub(intersect, &result->closest->position);
	vec_normalize(normal);
	*color = result->closest->mat.color;
}

void	compute_plane_light(t_vec3 *normal, t_color *color, t_result *result)
{
	*normal = result->closest->normal;
	*color = result->closest->mat.color;
}

void	compute_cylinder_light(t_vec3 *normal, t_point3 *intersect,
								t_color *color, t_result *result)
{
	t_shape	*cyl;

	assert("Normal" && normal);
	assert("Intersect" && intersect);
	assert("Color" && color);
	assert("Result" && result);
	cyl = result->closest;
	*normal = get_cylinder_normal(cyl, intersect);
	*color = cyl->mat.color;
}

void		handle_plane_intersect(double t[2], t_shape *tmp, t_range range, t_result *result)
{
	if (is_in_range(t[0], range) && t[0] < result->closest_t)
	{
		result->closest = tmp;
		result->closest_t = t[0];
	}
}

void		handle_sphere_intersect(double t[2], t_shape *tmp, t_range range, t_result *result)
{
	if (is_in_range(t[0], range) && t[0] < result->closest_t)
	{
		result->closest = tmp;
		result->closest_t = t[0];
	}
	if (is_in_range(t[1], range) && t[1] < result->closest_t)
	{
		result->closest = tmp;
		result->closest_t = t[1];
	}
}

void	handle_cylinder_intersect(double t[2], t_shape *cyl, t_range range, t_result *result)
{
	if (is_in_range(t[0], range) && t[0] < result->closest_t)
	{
		result->closest = cyl;
		result->closest_t = t[0];
	}
	if (is_in_range(t[1], range) && t[1] < result->closest_t)
	{
		result->closest = cyl;
		result->closest_t = t[1];
	}
}

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
		if (tmp->type == SPHERE && hit_sphere(origin, dir, tmp, t))
			handle_sphere_intersect(t, tmp, range, &result);
		else if (tmp->type == PLANE && hit_plane(origin, dir, tmp, t))
			handle_plane_intersect(t, tmp, range, &result);
		else if (tmp->type == CYLINDER && hit_cylinder(origin, dir, tmp, t))
			handle_cylinder_intersect(t, tmp, range, &result);
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
static t_color	compute_light(t_point3 *origin, t_vec3 *dir, t_result *result)
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
	intersect.x += dir->x * result->closest_t; // Make a point3_add function for this.
	intersect.y += dir->y * result->closest_t;
	intersect.z += dir->z * result->closest_t;
	if (result->closest->type == SPHERE)
		compute_sphere_light(&normal, &intersect, &color, result);
	else if (result->closest->type == PLANE)
		compute_plane_light(&normal, &color, result);
	else if (result->closest->type == CYLINDER)
		compute_cylinder_light(&normal, &intersect, &color, result);
	intensity = clamp(
			get_light_intensity(&intersect, &normal, result->closest->mat.specular),
			new_range(0.0, 1.0));
	color.r *= intensity;
	color.g *= intensity;
	color.b *= intensity;
	return (color);
}


/**
 * @brief Finds the closest object to the `origin` on a ray with `direction`,
 * and returns its color.
 */
t_color	ray_color(t_point3 origin, t_vec3 dir, t_range t_range, int depth)
{
	t_result	result;
	t_color		local_color;
	t_color		reflected;
	float		r;
	
	result = closest_intersect(&origin, &dir, t_range);
	if (!result.closest)
		return ((t_color)SKY_COLOR);
	local_color = compute_light(&origin, &dir, &result);
	r = result.closest->mat.reflection;
	if (depth <= 0 || r <= 0.0f)
		return local_color;
	reflected = compute_reflection(&origin, &dir, &result, depth);
	return (add_color(scale_color(local_color, 1 - r), reflected));
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
			new_range(1, INFINITY), MAXDEPTH
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
