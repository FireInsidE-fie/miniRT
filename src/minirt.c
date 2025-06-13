#include "minirt.h"
#include "camera.h"
#include "mlx.h"
#include "point3.h"
#include "scene.h"
#include "sphere.h"

#include <stdlib.h>
#include <stdio.h>

int	rt_kill(t_core *core, int exit_code)
{
	printf("[!] - Closing miniRT...\n");
	clear_scene(get_scene());
	mlx_destroy_image(core->mlx, core->img.img);
	mlx_destroy_window(core->mlx, core->win);
	mlx_destroy_display(core->mlx);
	free(core->mlx);
	return (exit(exit_code), exit_code);
}

void	test_scene(void)
{
	create_sphere(make_point3(0.0, 0.0, 5.0), 1, make_color(1.0, 0.0, 0.0));
	create_sphere(make_point3(1.0, 1.0, 3.0), 1, make_color(0.0, 1.0, 0.0));
	create_sphere(make_point3(-1.0, -1.0, 7.0), 1, make_color(0.0, 0.0, 1.0));
	create_sphere(make_point3(0.0, 0.0, 0.0), 1000, make_color(1.0, 0.0, 1.0));
	for (float i = 0.0; i <= 1.0; i += 0.1)
		create_sphere(make_point3(-5.0 + (i * 10), -8.0, 20.0), 1, make_color(i, i, i));
	create_camera(make_point3(0.0, 0.0, 0.0), make_point3(1.0, 0.0, 0.0), 90);
}

int	main(void)
{
	t_core	*core;

	test_scene();
	print_scene(get_scene());
	printf("================\n");
	init_window();
	core = get_core();
	core->img.img = mlx_new_image(core->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!core->img.img)
		rt_kill(core, 1);
	core->img.addr = mlx_get_data_addr(
			core->img.img,
			&core->img.bpp,
			&core->img.line_len,
			&core->img.endian
			);
	render(get_core(), &get_scene()->camera);
	printf("================\n");
	mlx_loop(get_core()->mlx);
}
