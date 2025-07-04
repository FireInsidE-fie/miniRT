#include "color.h"
#include "minirt.h"
#include "mlx.h"
#include "libft.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>

#define KEY_R 114
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_UP 65362
#define KEY_RIGHT 65363
#define KEY_DOWN 65364

/**
 * @brief The "core" struct of the program contains MLX-related data, the scene
 * and the mlx image the render is going to be written to.
 * @see The `minirt.h` file for the struct itself.
 */
t_core	*get_core(void)
{
	static t_core	core;

	if (!core.mlx)
	{
		core.mlx = mlx_init();
		ft_bzero(&core.scene, sizeof(t_scene));
	}
	return (&core);
}

void	swap_render_mode(t_core *core)
{
	if (core->render_mode == 1)
		core->render_mode = 0;
	else
	{
		printf("Rendering\n");
		core->render.is_rendering = 1;
		core->render_mode = 1;
	}
	// Reset render
	core->render.x = -WIN_WIDTH / 2;
	core->render.y = -WIN_HEIGHT / 2;

	if (core->render_mode == 0)
		mlx_loop_hook(core->mlx, fast_render_loop, core);
	else
		mlx_loop_hook(core->mlx, render_loop, core);
}


/**
 * @brief MLX trigger for key presses, closing the window when `ESC` is pressed.
 */
static int	key_press(int key, void *param)
{
	t_core	*core;

	core = param;
	if (key == KEY_ESC)
		return (rt_kill(core, 0));
	if (key == KEY_R && get_core()->render.is_rendering == 0)
		swap_render_mode(core);
	if (key == KEY_LEFT && get_core()->render_mode == 0)
		get_core()->scene.camera.position.x-=0.3;
	if (key == KEY_RIGHT && get_core()->render_mode == 0)
		get_core()->scene.camera.position.x+=0.3;
	if (key == KEY_UP && get_core()->render_mode == 0)
		get_core()->scene.camera.position.y+=0.3;
	if (key == KEY_DOWN && get_core()->render_mode == 0)
		get_core()->scene.camera.position.y-=0.3;
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
