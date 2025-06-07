#include "camera.h"
#include "minirt.h"
#include "mlx.h"
#include "point3.h"
#include "color.h"
#include "scene.h"
#include "sphere.h"
#include "math.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Finds the closest object to the `origin` on a ray with `direction`,
 * and returns its color.
 */
static t_color	ray_color(t_point3 origin, t_vec3 dir, double tmin, double tmax)
{
	t_scene		*scene;
	t_sphere	*tmp;
	t_sphere	*closest;
	double		t[2];
	double		closest_t;

	closest_t = (double)INFINITY;
	closest = NULL;
	scene = get_scene();
	tmp = scene->spheres;
	while (tmp)
	{
		if (hit_sphere(origin, dir, tmp, t))
		{
			if (t[0] <= tmax && t[0] >= tmin && t[0] < closest_t)
			{
				closest = tmp;
				closest_t = t[0];
			}
			if (t[1] <= tmax && t[1] >= tmin && t[1] < closest_t)
			{
				closest = tmp;
				closest_t = t[1];
			}
		}
		tmp = tmp->next;
	}
	if (closest)
		return (closest->color);
	return (t_color){1.0, 1.0, 1.0};
}

int	render(t_core *core, t_camera *camera)
{
	int		x;
	int		y;
	t_color	color;

	y = -WIN_HEIGHT / 2;
	while (y <= WIN_HEIGHT / 2)
	{
		x = -WIN_WIDTH / 2;
		while (x <= WIN_WIDTH / 2)
		{
			printf("[!] - Rendering pixel x%d-y%d...\r", x, y);
			color = ray_color(
				camera->position, camera_to_viewport(x, y), 1, INFINITY
			);
			mlx_pixel_put(core->mlx, core->win, x + WIN_WIDTH / 2, y + WIN_HEIGHT / 2, color_to_int(color));
			x++;
		}
		y++;
	}
	printf("[!] - Rendering complete.\n");
	return (0);
}
