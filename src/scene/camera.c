#include "scene.h"
#include "camera.h"
#include "point3.h"

void	create_camera(t_point3 position, t_vec3 direction, double fov)
{
	t_camera	*camera;

	camera = &get_scene()->camera;
	camera->position = position;
	camera->direction = direction;
	camera->fov = fov;
}
