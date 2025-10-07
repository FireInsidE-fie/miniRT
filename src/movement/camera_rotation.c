/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:29:22 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:29:22 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "movement.h"

#include <math.h>
#include <X11/X.h>
#include <stdint.h>

/**
 * @brief Rodrigues' rotation formula
 * Give it the direction, the axis you want to rotate (Right/Up)
 * and the angle you want to apply on the axis, and boom, works.
 * rotate_vector(cam->direction, cam->up, -0.3) < Cam goes down.
 */
t_vec3	rotate_vector(t_vec3 v, t_vec3 u, float angle)
{
	vec_normalize(&u);
	return (
		vec_add(
			vec_add(
				vec_scale(v, cos(angle)),
				vec_scale(cross_product(&u, &v), sin(angle))
			),
			vec_scale(u, dot_product(&u, &v) * (1 - cos(angle))))
	);
}

/**
 * @brief Remake a camera with the correct vectors
 * This is needed as when we apply a rotation of any kind,
 * the other vectors are not aligned anymore.
 * If we look a bit on the left or right with the camera,
 * we need to reassign where the Forward and Up vectors are.
 */
void	camera_build_basis(t_camera *cam)
{
	vec_normalize(&cam->forward);
	cam->right = cross_product(&(t_point3){0, 1, 0}, &cam->forward);
	vec_normalize(&cam->right);
	cam->up = cross_product(&cam->forward, &cam->right);
	vec_normalize(&cam->up);
}

/**
 * @brief Builds a new camera with a new Up/down angle applied.
 * The Pitch is also capped so we don't go too far and end up
 * looking "behind" by going completely Up or Down.
 * Takes care of clamping the value to avoid clipping.
 */
void	rotate_camera_pitch(t_camera *cam, float angle)
{
	float	new_pitch;

	new_pitch = cam->pitch + angle;
	if (new_pitch > M_PI / 2.0 - 0.01)
		angle = (M_PI / 2.0 - 0.01) - cam->pitch;
	else if (new_pitch < -M_PI / 2.0 + 0.01)
		angle = (-M_PI / 2.0 + 0.01) - cam->pitch;
	cam->forward = rotate_vector(cam->forward, cam->right, angle);
	cam->pitch += angle;
	camera_build_basis(cam);
}

/**
 * @brief Builds a new camera with a new Left/Right angle applied.
 */
void	rotate_camera_yaw(t_camera *cam, float angle)
{
	cam->forward = rotate_vector(cam->forward, cam->up, angle);
	camera_build_basis(cam);
}
