#include "scene.h"
#include "camera.h"
#include "point3.h"
#include "minirt.h"

#include <assert.h>
#include <stdio.h>

void	create_camera(t_point3 position, t_vec3 direction, float fov)
{
	t_camera	*camera;

	assert("Field of view" && fov > 0 && fov < 180);
	camera = &get_core()->scene.camera;
	camera->position = position;
	camera->direction = direction;
	camera->fov = fov;
}

void	print_camera(t_camera *camera)
{
	assert("Camera" && camera);
	printf("[!] - Camera\n"
		"Position: (%f, %f, %f)\n"
		"Direction: (%f, %f, %f)\n"
		"Field of View: %f\n",
		camera->position.x, camera->position.y, camera->position.z,
		camera->direction.x, camera->direction.y, camera->direction.z,
		camera->fov);
}

/**
 * @brief For a pixel on the camera's viewport, find a vector from
 * the camera's origin that passes through that pixel.

 * @note The distance between the camera and the viewport canvas is 1 (unit
 * length).
 */
t_vec3	camera_to_viewport(int x, int y)
{
	return (
		(t_vec3)
		{
			.x = x * (1.0 / (float)WIN_WIDTH),
			.y = -y * (1.0 / (float)WIN_HEIGHT),
			.z = 1.0
		}
	);
}
