#include "scene.h"

#include <stdlib.h>

/**
 * @brief Static getter for the miniRT scene.
 */
t_scene	*get_scene(void)
{
	static t_scene	scene;

	return (&scene);
}

/**
 * @brief Clears a linked list of elements
 *
 * @note Could be expanded to take in a function pointer in case we need to
 * clear specific stuff inside of each node.
 */
static void	clear_list(void *first)
{
	t_sphere	*current;
	t_sphere	*next;

	current = first;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	clear_scene(t_scene *scene)
{
	clear_list(scene->spheres);
	// clear_list(scene->lights);
	// clear_list(scene->planes);
	// clear_list(scene->cylinders);
}
