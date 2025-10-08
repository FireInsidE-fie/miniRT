/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:25:14 by nrey              #+#    #+#             */
/*   Updated: 2025/10/08 16:47:26 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "camera.h"
#include "point3.h"
#include "minirt.h"
#include "vector.h"

#include <math.h>
#include <stdio.h>

t_vec3	camera_apply_rotation(t_vec3 v, t_camera *cam)
{
	return (
		(t_vec3){
		v.x * cam->right.x + v.y * cam->up.x + v.z * cam->forward.x,
		v.x * cam->right.y + v.y * cam->up.y + v.z * cam->forward.y,
		v.x * cam->right.z + v.y * cam->up.z + v.z * cam->forward.z
	}
	);
}

/**
 * @brief Sets the camera to default values in case it is missing in the
 * .rt map.
 */
void	default_camera(t_camera *camera)
{
	camera->fov = 70;
	camera->ar = (float)WIN_WIDTH / WIN_HEIGHT;
	camera->forward = (t_vec3){0.0, 0.0, 1.0};
	camera->right = (t_vec3){1.0, 0.0, 0.0};
	camera->up = (t_vec3){0.0, 1.0, 0.0};
}

void	create_camera(t_point3 *position, t_vec3 *direction, float fov)
{
	t_camera	*camera;
	t_vec3		world_up;

	world_up = (t_vec3){0.0f, 1.0f, 0.0f};
	camera = &get_scene()->camera;
	camera->position = *position;
	camera->ar = (float)WIN_WIDTH / WIN_HEIGHT;
	camera->fov = fov;
	camera->forward = *direction;
	vec_normalize(&camera->forward);
	if (fabs(camera->forward.y) > 0.999f)
		world_up = (t_vec3){0.0f, 0.0f, 1.0f};
	camera->right = cross_product(&world_up, &camera->forward);
	vec_normalize(&camera->right);
	camera->up = cross_product(&camera->right, &camera->forward);
	vec_normalize(&camera->up);
	camera->up = point3_scale(&camera->up, -1);
}

void	print_camera(t_camera *camera)
{
	printf("[!] - Camera\n"
		"Position: (%f, %f, %f)\n"
		"Direction: (%f, %f, %f)\n"
		"Field of View: %f\n",
		camera->position.x, camera->position.y, camera->position.z,
		camera->forward.x, camera->forward.y, camera->forward.z,
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
	float	viewport_half_width;
	float	viewport_half_height;

	viewport_half_width = tan(get_scene()->camera.fov * M_PI / 180.0f / 2.0f);
	viewport_half_height = viewport_half_width / get_scene()->camera.ar;
	return (
		(t_vec3)
		{
			.x = x / (float)WIN_WIDTH * viewport_half_width,
			.y = -y / (float)WIN_HEIGHT * viewport_half_height,
			.z = 1.0f
		}
	);
}
