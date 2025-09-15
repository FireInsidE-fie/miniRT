#ifndef CAMERA_H
# define CAMERA_H

# include "point3.h"

typedef struct s_camera
{
	t_point3	position;
	t_vec3		direction;
	t_vec3		up;
	t_vec3		right;
	t_vec3		forward;
	float		pitch;
	float		ar;
	float		fov;		// Range [0, 180]
}	t_camera;

void	create_camera(t_point3 *position, t_vec3 *direction, float fov);
void	print_camera(t_camera *camera);
t_vec3	camera_to_viewport(int x, int y);
t_vec3	camera_apply_rotation(t_vec3 v, t_camera *cam);

#endif // CAMERA_H
