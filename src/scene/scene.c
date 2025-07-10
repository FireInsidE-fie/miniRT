#include "scene.h"
// #include "ambient.h"
// #include "sphere.h"
// #include "light.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief Clears a linked list of elements
 *
 * @note Could be expanded to take in a function pointer in case we need to
 * clear specific stuff inside of each node.
 */
void	clear_list(void *first)
{
	t_shape	*current;
	t_shape	*next;

	assert("First" && first);
	current = first;
	while (current)
	{
		printf("[!] - Freed one object.\n");
		next = current->next;
		free(current);
		current = next;
	}
}

/**
 * @brief Debug print statements to display the current scene as understood by
 * miniRT.
 * Should be veeeeeery useful for parsing.
 */
void	print_scene(t_scene *scene)
{
	// void	*tmp;

	assert("Scene" && scene);
	printf("[!] - NOT Printing scene (function needs rewriting)...\n");
	// printf("======== Camera ========\n");
	// print_camera(&scene->camera);
	// printf("======== Ambient ========\n");
	// print_ambient(&scene->ambient);
	// printf("======== Spheres ========\n");
	// tmp = scene->shapes;
	// while (tmp)
	// {
	// 	print_sphere(tmp);
	// 	tmp = ((t_shape *)tmp)->next;
	// }
	// printf("======== Lights ========\n");
	// tmp = scene->lights;
	// while (tmp)
	// {
	// 	print_light(tmp);
	// 	tmp = ((t_light *)tmp)->next;
	// }
	// printf("======== Planes ========\n");
	// tmp = scene->planes;
	// while (tmp)
	// {
	// 	print_plane(tmp);
	// 	tmp = ((t_plane *)tmp)->next;
	// }
	// printf("======== Cylinders ========\n");
	// tmp = scene->cylinders;
	// while (tmp)
	// {
	// 	print_cylinder(tmp);
	// 	tmp = ((t_cylinder *)tmp)->next;
	// }
}
