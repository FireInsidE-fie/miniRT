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

#define BLOCK_SIZE 480
#define FAST_STEP 10

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
t_color	compute_light(t_point3 *origin, t_vec3 *dir, t_result *result)
{
	t_point3	intersect;
	t_vec3		normal;
	t_color		color;

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
	color.r *= clamp(
			get_light_intensity(&intersect, &normal, result->closest->mat.specular),
			new_range(0.0, 1.0));
	color.g *= clamp(
			get_light_intensity(&intersect, &normal, result->closest->mat.specular),
			new_range(0.0, 1.0));
	color.b *= clamp(
			get_light_intensity(&intersect, &normal, result->closest->mat.specular),
			new_range(0.0, 1.0));
	return (color);
}

/**
 * @brief Finds the closest object to the `origin` on a ray with `direction`,
 * and returns its color.
 */
static t_color	ray_color(t_point3 origin, t_vec3 dir, t_range t_range)
{
	t_result	result;

	result = closest_intersect(&origin, &dir, t_range);
	if (result.closest)
		return (compute_light(&origin, &dir, &result));
	return ((t_color)SKY_COLOR);
}

/**
 * @brief For every 10x10 pixels, prints the color.
 * Called inside the fast render func.
 */
void	process_fast_steps(void)
{
	int		i;
	int		j;
	t_color	color;

	color = ray_color(
			get_scene()->camera.position,
			camera_to_viewport(get_core()->render.x, get_core()->render.y),
			new_range(1, INFINITY)
			);
	j = 0;
	while (j < FAST_STEP && get_core()->render.y + j <= WIN_HEIGHT / 2)
	{
		i = 0;
		while (i < FAST_STEP && get_core()->render.x + i <= WIN_WIDTH / 2)
		{
			img_put_pixel(&get_core()->img,
				get_core()->render.x + i + WIN_WIDTH / 2,
				get_core()->render.y + j + WIN_HEIGHT / 2,
				&color);
			i++;
		}
		j++;
	}
}

/**
 * @brief Simple rendering.
 * Only prints every 10 pixels (FAST_STEP) to be less heavy on the cpu.
 */
int	fast_render_loop(void *param)
{
	(void)param;
	get_core()->render.y = -WIN_HEIGHT / 2;
	while (get_core()->render.y <= WIN_HEIGHT / 2)
	{
		get_core()->render.x = -WIN_WIDTH / 2;
		while (get_core()->render.x <= WIN_WIDTH / 2)
		{
			process_fast_steps();
			get_core()->render.x += FAST_STEP;
		}
		get_core()->render.y += FAST_STEP;
	}
	mlx_put_image_to_window(
		get_core()->mlx, get_core()->win, get_core()->img.img, 0, 0
		);
	return (0);
}

/**
 * @brief Gets called inside the double while statement of the render loop.
 * Prints each pixel for each blocks.
 */
void	process_bloc_render(void)
{
	t_color	color;

	color = ray_color(
			get_scene()->camera.position,
			camera_to_viewport(get_core()->render.x, get_core()->render.y),
			new_range(1, INFINITY)
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
int	render_loop(void *param)
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
		get_core()->mlx, get_core()->win, get_core()->img.img, 0, 0
		);
	return (0);
}

/**
 * @brief The main render loop, sending a ray through each pixel on the
 * viewport's canvas, and getting the color that ray (and pixel) is going to be.
 *
 * @note We have to start `x` and `y` at a value before 0, because the center
 * of the camera is the (0, 0) point of the canvas. If we started at (0, 0),
 * the camera would be offset on the lower right.
 */
int	render(t_core *core, t_camera *camera)
{
	int		x;
	int		y;
	t_color	color;

	assert("Core" && core);
	assert("Camera" && camera);
	y = -WIN_HEIGHT / 2;
	while (y <= WIN_HEIGHT / 2)
	{
		x = -WIN_WIDTH / 2;
		printf("[!] - Rendering row %d...\r", y);
		while (x <= WIN_WIDTH / 2)
		{
			color = ray_color(
					camera->position,
					camera_to_viewport(x, y),
					new_range(1, INFINITY)
					);
			img_put_pixel(&core->img,
				x + WIN_WIDTH / 2, y + WIN_HEIGHT / 2, &color);
			++x;
		}
		mlx_put_image_to_window(core->mlx, core->win, core->img.img, 0, 0);
		++y;
	}
	printf("[!] - Rendering complete.\n");
	return (0);
}
