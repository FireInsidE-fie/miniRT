#ifndef CAMERA_H
# define CAMERA_H

# include "point3.h"

typedef struct s_camera
{
	t_point3	position;
	t_vec3		direction;
	double		fov;		// Range [0, 180]
}	t_camera;

void	create_camera(t_point3 position, t_vec3 direction, double fov);

#endif // CAMERA_H
