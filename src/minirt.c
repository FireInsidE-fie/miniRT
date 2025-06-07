#include "minirt.h"
#include "camera.h"
#include "mlx.h"
#include "point3.h"
#include "scene.h"
#include "sphere.h"

#include <stdlib.h>
#include <stdio.h>

int	rt_kill(t_core *core)
{
	printf("[!] - Closing miniRT...\n");
	clear_scene(get_scene());
	mlx_destroy_window(core->mlx, core->win);
	mlx_destroy_display(core->mlx);
	free(core->mlx);
	return (exit(0), 0);
}

int	main(void)
{
	t_camera	*camera;
	double		t[2];

	create_sphere(make_point3(0.0, 0.0, 5.0), 1, make_color(1.0, 0.0, 0.0));
	create_sphere(make_point3(1.0, 1.0, 3.0), 1, make_color(0.0, 1.0, 0.0));
	create_sphere(make_point3(-1.0, -1.0, 7.0), 1, make_color(0.0, 0.0, 1.0));
	create_camera(make_point3(0.0, 0.0, 0.0), make_point3(1.0, 0.0, 0.0), 90);
	print_scene(get_scene());
	camera = &get_scene()->camera;
	printf("================\n");
	printf("[!] - Sphere hit: %i\n",
		hit_sphere(camera->position, camera->direction,
		get_scene()->spheres, t)
	);
	init_window();
	render(get_core(), camera);
	mlx_loop(get_core()->mlx);
}
