#include "export.h"
#include <fcntl.h>
#include <stdio.h>

void	export_scene(void)
{
	int		fd;
	t_scene	*scene;
	t_light	*lights;
	t_shape	*shape;

	scene = get_scene();
	lights = scene->lights;
	shape = scene->shapes;
	fd = open("exported.rt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	export_meta(scene, lights, fd);
	export_shapes(shape, fd);
}
