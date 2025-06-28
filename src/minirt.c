#include "minirt.h"
#include "ambient.h"
#include "camera.h"
#include "color.h"
#include "mlx.h"
#include "point3.h"
#include "scene.h"
#include "sphere.h"
#include "light.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief Closes the program and cleans its heap-allocated memory.
 * Also takes care of MLX ressources.
 */
int	rt_kill(t_core *core, int exit_code)
{
	assert("Core" && core);
	printf("[!] - Closing miniRT...\n");
	clear_scene(&core->scene);
	mlx_destroy_image(core->mlx, core->img.img);
	mlx_destroy_window(core->mlx, core->win);
	mlx_destroy_display(core->mlx);
	free(core->mlx);
	return (exit(exit_code), exit_code);
}

void	test_scene(void)
{
	create_sphere(make_point3(1.0, -1.0, 3.0), 1, make_color(1.0, 0.0, 0.0));
	create_sphere(make_point3(0.0, 0.0, 5.0), 1, make_color(0.0, 1.0, 0.0));
	create_sphere(make_point3(-1.0, 1.0, 7.0), 1, make_color(0.0, 0.0, 1.0));

	create_sphere(make_point3(0.0, -101.0, 0.0), 100, make_color(1.0, 0.0, 1.0));

	for (float i = 0.0; i <= 1.0; i += 0.1)
		create_sphere(make_point3(-5.0 + (i * 10), 8.0, 20.0), 1, make_color(i, i, i));

	create_light(make_point3(10.0, 20.0, 10.0), 0.8, make_color(1.0, 1.0, 1.0));

	create_ambient(0.5, make_color(1.0, 1.0, 1.0));

	create_camera(make_point3(0.0, 0.0, 0.0), make_point3(1.0, 0.0, 0.0), 90.0);
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
	render(get_core(), &core->scene.camera);
	printf("================\n");
	mlx_loop(get_core()->mlx);
}
