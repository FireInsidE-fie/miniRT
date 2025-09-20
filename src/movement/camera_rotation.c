#include "vector.h"
#include "movement.h"

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
				vec_scalar(v, cos(angle)),
				vec_scalar(cross_product(&u, &v), sin(angle))
			),
			vec_scalar(u, dot_product(&u, &v) * (1 - cos(angle))))
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
 */
void	rotate_camera_pitch(t_camera *cam, float angle)
{
	float	new_pitch;

	new_pitch = cam->pitch + angle;
	// Clamp avoiding clipping
	if (new_pitch > MAX_PITCH_RAD)
		angle = MAX_PITCH_RAD - cam->pitch;
	else if (new_pitch < MIN_PITCH_RAD)
		angle = MIN_PITCH_RAD - cam->pitch;
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
