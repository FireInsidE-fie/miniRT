#include "minirt.h"
#include "ambient.h"
#include "camera.h"
#include "material.h"
#include "mlx.h"
#include "point3.h"
#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"
#include "light.h"
#include "libft.h"

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

	if (!core.mlx)
	{
		core.mlx = mlx_init();
		ft_bzero(&core.scene, sizeof(t_scene));
	}
	return (&core);
}

/**
 * @brief Closes the program and cleans its heap-allocated memory.
 * Also takes care of MLX ressources.
 */
int	rt_kill(t_core *core, int exit_code)
{
	assert("Core" && core);
	printf("[!] - Closing miniRT...\n");
	if (core->prevent_close)
		return (printf("[!] - Close edit Window before quitting\n"), 0);
	clear_lights(core->scene.lights);
	clear_shapes(core->scene.shapes);
	mlx_destroy_image(core->mlx, core->img.img);
	mlx_destroy_image(core->mlx, core->ui_img.img);
	mlx_destroy_window(core->mlx, core->altwin);
	mlx_destroy_window(core->mlx, core->win);
	mlx_destroy_display(core->mlx);
	free(core->mlx);
	return (exit(exit_code), exit_code);
}

/**
 * @brief Temporary function to test scene creation and rendering. Will be
 * removed once parsing is here.
 */
void	test_scene(void)
{
	t_vec3 normalplane; // don't mind the 3 following lines we just need a normalized vector beforehand so far.

	normalplane = make_vec3(0.0, 1.0, 0.0);
	vec_normalize(&normalplane);
	create_plane(make_point3(0.0, -1.0, 0.0), normalplane, make_mat(make_color(0.3, 0.3, 0.4), 1000, 0.0f));

	create_cylinder(
		make_point3(10.0, 3.0, 5.0),
		make_vec3(0.0, 1.0, 0.0),
		0.4,
		3.0,
		make_mat(make_color(1.0, 0.0, 0.0), 500, 0.5)
	);
	create_sphere(
		make_point3(10.0, 6.0, 5.0),
		0.7,
		make_mat(make_color(1.0, 0.0, 0.0), 1000, 0.2f)
	);
	create_sphere(
		make_point3(10.0, 3.0, 5.0),
		0.7,
		make_mat(make_color(1.0, 0.0, 0.0), 1000, 0.2f)
	);
	create_sphere(
		make_point3(1.0, -1.0, 3.0),
		1,
		make_mat(make_color(0.86, 1.0, 0.21), 1000, 0.2f)
	);
	create_sphere(
		make_point3(0.0, 0.0, 5.0),
		1,
		make_mat(make_color(0.0, 1.0, 0.0), 1000, 0.3f)
	);
	create_sphere(
		make_point3(-1.0, 1.0, 7.0),
		1,
		make_mat(make_color(0.0, 0.0, 1.0), 1000, 0.4f)
	);

	for (float i = 0.0; i <= 1.0; i += 0.1)
		create_sphere(
			make_point3(-5.0 + (i * 10), 8.0, 20.0),
			1,
			make_mat(make_color(i, i, i), 1000, 0.5)
		);

	create_light(
		make_point3(-7.0, 10.0, 15.0),
		0.9,
		make_color(1.0, 1.0, 1.0)
	);

	create_ambient(0.2, make_color(1.0, 1.0, 1.0));

	create_camera(
		make_point3(0.0, 0.0, 0.0),
		make_point3(1.0, 0.0, 0.0),
		90.0
	);
}

int	main(void)
{
	t_core	*core;

	core = get_core();
	test_scene();
	print_scene(&core->scene);
	printf("================\n");
	init_window();
	core->img.img = mlx_new_image(core->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!core->img.img)
		rt_kill(core, 1);
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
