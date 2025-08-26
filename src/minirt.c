#include "minirt.h"
#include "mlx.h"
#include "scene.h"
#include "light.h"
#include "libft.h"
#include "parsing.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief The "core" struct of the program contains MLX-related data, the scene
 * and the mlx image the render is going to be written to.
 * @see The `minirt.h` file for the struct itself.
 */
t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

/**
 * @brief Closes the program and cleans its heap-allocated memory.
 * Also takes care of MLX ressources.
 */
int	rt_kill(int exit_code)
{
	t_core	*core;

	core = get_core();
	if (core->prevent_close)
		return (printf("[!] - Close edit Window before quitting\n"), 0);
	printf("[!] - Closing miniRT...\n");
	clear_lights(core->scene.lights);
	clear_shapes(core->scene.shapes);
	if (core->mlx)
	{
		mlx_destroy_image(core->mlx, core->img.img);
		mlx_destroy_image(core->mlx, core->ui_img.img);
		mlx_destroy_window(core->mlx, core->altwin);
		mlx_destroy_window(core->mlx, core->win);
		mlx_destroy_display(core->mlx);
		free(core->mlx);
	}
	return (exit(exit_code), exit_code);
}

int	main(int argc, char **argv)
{
	t_core	*core;
	int		parse_status;

	if (argc != 2)
		return (-1);
	core = get_core();
	ft_bzero(&core->scene, sizeof(t_scene));
	parse_status = parse_scene(argv[1]);
	if (parse_status != 0)
		return (printf("[!] - Error during parsing!\n"), rt_kill(parse_status));
	print_scene(&core->scene);
	printf("================\n");
	init_window();
	core->img.img = mlx_new_image(core->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!core->img.img)
		rt_kill(1);
	core->img.addr = mlx_get_data_addr(
			core->img.img,
			&core->img.bpp,
			&core->img.line_len,
			&core->img.endian
			);
	core->render_mode = 0;
	core->render.is_rendering = 0;
	core->page_idx = 0;
	core->prevent_close = 0;
	mlx_loop_hook(core->mlx, fast_render, core);
	printf("================\n");
	mlx_mouse_hook(core->altwin, on_mouse_debug, core);
	mlx_loop(get_core()->mlx);
}
