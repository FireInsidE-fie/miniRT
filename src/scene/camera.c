#include "scene.h"
#include "camera.h"
#include "point3.h"

#include <stdio.h>

void	create_camera(t_point3 position, t_vec3 direction, double fov)
{
	t_camera	*camera;

	camera = &get_scene()->camera;
	camera->position = position;
	camera->direction = direction;
	camera->fov = fov;
}

void	print_camera(t_camera *camera)
{
	printf("[!] - Camera\n"
		"Position: (%f, %f, %f)\n"
		"Direction: (%f, %f, %f)\n"
		"Field of View: %f\n",
		camera->position.x, camera->position.y, camera->position.z,
		camera->direction.x, camera->direction.y, camera->direction.z,
		camera->fov);
}
