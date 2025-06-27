#ifndef SCENE_H
# define SCENE_H

# include "ambient.h"
# include "camera.h"
# include "light.h"
# include "sphere.h"
# include "plane.h"
# include "cylinder.h"

// Structs //

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_scene;

// Functions //

void		clear_scene(t_scene *scene);
void		print_scene(t_scene *scene);

#endif // SCENE_H
