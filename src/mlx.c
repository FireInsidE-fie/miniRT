#include "color.h"
#include "minirt.h"
#include "mlx.h"

#include <X11/X.h>
#include <stdint.h>

#define KEY_ESC 65307

t_core	*get_core(void)
{
	static t_core	core;

	if (!core.mlx)
		core.mlx = mlx_init();
	return (&core);
}

static int	key_press(int key, void *param)
{
	t_core	*core;

	core = param;
	if (key == KEY_ESC)
		return (rt_kill(core, 0));
	return (0);
}

/**
 * @brief Creates hooks for the minilibX, quitting the program when the main
 * window is destroyed or the `ESC` key is pressed.
 */
static void	init_hooks(t_core *core)
{
	core = get_core();
	mlx_hook(core->win, KeyPress, KeyPressMask, key_press, core);
	mlx_hook(core->win, DestroyNotify, 0, rt_kill, core);
}

/**
 * @brief Creates the MLX window.
 *
 * @return 0 if all went well, 1 if window initialization failed.
 */
int	init_window(void)
{
	t_core	*core;

	core = get_core();
	core->win
		= mlx_new_window(core->mlx, WIN_WIDTH, WIN_HEIGHT, "Obsolete Meat");
	if (!core->win)
		return (1);
	init_hooks(core);
	return (0);
}

/**
 * @brief Puts a given color on a pixel of a MLX image.
 */
void	img_put_pixel(t_img *img, int x, int y, t_color *color)
{
	char	*dest;

	dest = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(uint32_t *)dest = color_to_int(color);
}
