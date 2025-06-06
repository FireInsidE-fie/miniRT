#include "minirt.h"

/**
 * @brief Static getter for the miniRT scene.
 */
t_scene	*get_scene(void)
{
	static t_scene	scene;

	return (&scene);
}
