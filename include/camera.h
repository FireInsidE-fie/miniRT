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
void	print_camera(t_camera *camera);
t_vec3	camera_to_viewport(int x, int y);

#endif // CAMERA_H
