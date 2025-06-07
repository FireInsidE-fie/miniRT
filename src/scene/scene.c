#include "scene.h"
#include "sphere.h"

#include <stdlib.h>
#include <stdio.h>

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
		printf("[!] - Freed one object.\n");
		next = current->next;
		free(current);
		current = next;
	}
}

void	clear_scene(t_scene *scene)
{
	printf("[!] - Freeing spheres...\n");
	clear_list(scene->spheres);
	// clear_list(scene->lights);
	// clear_list(scene->planes);
	// clear_list(scene->cylinders);
}

void	print_scene(t_scene *scene)
{
	void	*tmp;

	printf("[!] - Printing scene...\n");
	printf("======== Camera ========\n");
	print_camera((t_camera *)&scene->camera);
	printf("======== Spheres ========\n");
	tmp = scene->spheres;
	while (tmp)
	{
		print_sphere(tmp);
		tmp = ((t_sphere *)tmp)->next;
	}
}
