#include "minirt.h"
#include "camera.h"
#include "mlx.h"
#include "point3.h"
#include "scene.h"
#include "sphere.h"

// Standard library //
#include <stdlib.h>

int	rt_kill(t_core *core)
{
	clear_scene(get_scene());
	mlx_destroy_window(core->mlx, core->win);
	mlx_destroy_display(core->mlx);
	free(core->mlx);
	return (exit(0), 0);
}

int	main(void)
{
	create_sphere(make_point3(5, 0, 0), 1, make_color(255, 0, 0));
	create_camera(make_point3(0, 0, 0), make_point3(1, 0, 0), 90);
	print_scene(get_scene());
	init_window();
	mlx_loop(get_core()->mlx);
}
