#include "minirt.h"
#include "mlx.h"

#include <math.h>

#define FAST_STEP 10

/**
 * @brief For every fast step block of pixels, output the same color as a block.
 * Called inside the fast render function.
 */
static void	process_fast_steps(void)
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
int	fast_render(void *param)
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
