#include "minirt.h"
#include "mlx.h"
#include "movement.h"
#include "export.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Swaps miniRT between full render and fast render modes.
 */
void	swap_render_mode(t_core *core)
{
	if (core->render_mode == 1)
		core->render_mode = 0;
	else
	{
		printf("[!] - Rendering...\n");
		core->render.is_rendering = 1;
		core->render_mode = 1;
	}
	core->render.x = -WIN_WIDTH / 2;
	core->render.y = -WIN_HEIGHT / 2;
	if (core->render_mode == 0)
		mlx_loop_hook(core->mlx, fast_render, core);
	else
		mlx_loop_hook(core->mlx, render, core);
}

/**
 * Core has a key_state int[256] array that contains the status of each key
 * pressed, up to 256 because most key codes are in that range
 * (damn you ESC and Arrow keys).
 * key_press sets the state to 1 when pressed/held, and key_release()
 * sets it back to 0.
 * update_camera() from camera_movement.c is called in the fast render loop,
 * applying the movements depending on the key_state value of each key.
*/
static int	key_press(int key, void *param)
{
	t_core	*core;

	core = param;
	if (key == KEY_ESC)
		rt_kill(0);
	if (key == KEY_R && core->render.is_rendering == 0)
		swap_render_mode(core);
	if (key >= 0 && key < 256)
		core->key_state[key] = 1;
	if (key == 112)
	{
		write(0, "EXPORTED\n", 9);
		export_scene();
	}
	return (0);
}

/**
 * @brief Creates hooks for the minilibX, listens for keypresses,
 * key releases and the closing button
 */
static int	key_release(int key, void *param)
{
	t_core	*core;

	core = param;
	if (key >= 0 && key < 256)
		core->key_state[key] = 0;
	if (key == 65507)
		core->key_state[112] = 0;
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
	mlx_hook(core->win, KeyRelease, KeyReleaseMask, key_release, core);
	mlx_hook(core->win, DestroyNotify, 0, rt_kill, 0);
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
	core->mlx = mlx_init();
	core->win
		= mlx_new_window(core->mlx, WIN_WIDTH, WIN_HEIGHT, "Obsolete Meat");
	if (!core->win)
		return (1);
	core->altwin
		= mlx_new_window(core->mlx, 400, 615, "Obsolete Meat - Hierarchy");
	render_shape_list(core);
	init_hooks(core);
	core->img.img = mlx_new_image(core->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!core->img.img)
		rt_kill(1);
	core->img.addr = mlx_get_data_addr(
			core->img.img,
			&core->img.bpp,
			&core->img.line_len,
			&core->img.endian
			);
	mlx_loop_hook(core->mlx, fast_render, core);
	mlx_mouse_hook(core->altwin, on_mouse_debug, core);
	mlx_loop(get_core()->mlx);
	return (0);
}
