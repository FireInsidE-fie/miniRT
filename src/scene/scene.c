#include "scene.h"

/**
 * @brief Static getter for the miniRT scene.
 */
t_scene	*get_scene(void)
{
	static t_scene	scene;

	return (&scene);
}

void	clear_scene(void)
{
	//clear_lights();
	clear_spheres();
	//clear_planes();
	//clear_cylinders();
}
