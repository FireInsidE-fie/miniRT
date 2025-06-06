#ifndef CAMERA_H
# define CAMERA_H

# include "point3.h"

typedef struct s_camera
{
	t_point3	origin;
	t_vec3		direction;
	int			fov;		// Range [0, 180]
}	t_camera;

#endif // CAMERA_H
