#include "camera.h"
#include "light.h"
#include "minirt.h"
#include "point3.h"
#include "color.h"
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
 * in direction `dir`, between `tmin` and `tmax`.
 *
 * @return A `t_result` struct containing a pointer to the sphere intersected
 * and the t value at that point.
 */
t_result	closest_intersect(t_point3 *origin, t_vec3 *dir, t_range t_range)
{
	t_sphere	*tmp;
	t_result	result;
	double		t[2];

	assert("Origin" && origin);
	assert("Direction" && dir);
	assert("T_range" && t_range.min >= 0.0);
	assert("T_range" && t_range.max >= t_range.min);
	result.closest = NULL;
	result.closest_t = t_range.max;
	tmp = get_core()->scene.spheres;
	while (tmp)
	{
		if (hit_sphere(origin, dir, tmp, t))
		{
			if (t[0] <= t_range.max && t[0] >= t_range.min && t[0] < result.closest_t)
			{
				result.closest = tmp;
				result.closest_t = t[0];
			}
			if (t[1] <= t_range.max && t[1] >= t_range.min && t[1] < result.closest_t)
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
 */
t_color	compute_light(t_point3 *origin, t_vec3 *dir, t_result result)
{
	t_point3	intersect;
	t_vec3		normal;
	t_color		color;

	assert("Origin" && origin);
	assert("Direction" && dir);
	assert("Closest" && result.closest);
	assert("Closest_t" && result.closest_t >= 0.0);
	intersect = *origin;
	intersect.x += dir->x * result.closest_t;
	intersect.y += dir->y * result.closest_t;
	intersect.z += dir->z * result.closest_t;
	normal = point3_sub(&intersect, &result.closest->center);
	vector_normalize(&normal);
	color = result.closest->color;
	color.r *= clamp(get_light_intensity(&intersect, &normal), new_range(0.0, 1.0));
	color.g *= clamp(get_light_intensity(&intersect, &normal), new_range(0.0, 1.0));
	color.b *= clamp(get_light_intensity(&intersect, &normal), new_range(0.0, 1.0));
	return (color);
}

/**
 * @brief Finds the closest object to the `origin` on a ray with `direction`,
 * and returns its color.
 */
// TODO: there's a big problem with the current approach. Since we have a
// distinct linked list for every type of object, we can't easily iterate over
// all object types when trying to find a ray color (spheres, planes, cylinders)
// As such, we could maybe for example create an array[number_of_types], with
// each slot in the array containing the head of the linked list related to that
// type. This would allow us to iterate over the array and each linked list
// contained within, in a single go.
static t_color	ray_color(t_point3 origin, t_vec3 dir, t_range t_range)
{
	t_result	r;

	r = closest_intersect(&origin, &dir, t_range);
	if (r.closest)
		return (compute_light(&origin, &dir, r));
	return ((t_color)SKY_COLOR);
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
