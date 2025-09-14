#include "scene.h"
#include "camera.h"
#include "point3.h"
#include "minirt.h"
#include "vector.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

t_vec3 camera_apply_rotation(t_vec3 v, t_camera *cam)
{
	return (
		(t_vec3){
		v.x * cam->right.x + v.y * cam->up.x + v.z * cam->forward.x,
		v.x * cam->right.y + v.y * cam->up.y + v.z * cam->forward.y,
		v.x * cam->right.z + v.y * cam->up.z + v.z * cam->forward.z
	}
	);
}

void	create_camera(t_point3 *position, t_vec3 *direction, float fov)
{
	t_camera	*camera;
	t_vec3		world_up;

	assert("Field of view" && fov >= 0 && fov <= 180);
	world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	camera = &get_scene()->camera;
	camera->position = *position;
	camera->hfov = fov;
	camera->vfov = 2.0f * atan(tan(camera->hfov / 180 * M_PI / 2.0f) / ((float)WIN_WIDTH / (float)WIN_HEIGHT)) * 180 / M_PI;
	camera->forward = *direction;
	vec_normalize(&camera->forward);
	camera->right = cross_product(&world_up, &camera->forward);
	vec_normalize(&camera->right);
	camera->up = cross_product(&camera->right, &camera->forward);
	vec_normalize(&camera->up);
	camera->up = point3_scale(&camera->up, -1);
}

void	print_camera(t_camera *camera)
{
	assert("Camera" && camera);
	printf("[!] - Camera\n"
		"Position: (%f, %f, %f)\n"
		"Direction: (%f, %f, %f)\n"
		"Horizontal / Vertical Fields of View: %f - %f\n",
		camera->position.x, camera->position.y, camera->position.z,
		camera->forward.x, camera->forward.y, camera->forward.z,
		camera->hfov, camera->vfov);
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
			.x = x * (get_scene()->camera.hfov / 180 / (float)WIN_WIDTH),
			.y = -y * (get_scene()->camera.vfov / 180 / (float)WIN_HEIGHT),
			.z = 1.0
		}
	);
}
