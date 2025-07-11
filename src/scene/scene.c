#include "minirt.h"
#include "scene.h"
#include "ambient.h"
#include "sphere.h"
#include "light.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief Static getter for the miniRT scene.
 */
t_scene	*get_scene(void)
{
	static t_scene	*scene;

	if (!scene)
		scene = &get_core()->scene;
	return (scene);
}

/**
 * @brief Appends a new shape at the end of the shapes linked list.
 */
void	add_shape(t_shape *new_shape)
{
	t_scene		*scene;
	t_shape		*tmp;

	scene = get_scene();
	if (!scene->shapes)
	{
		scene->shapes = new_shape;
		return ;
	}
	tmp = scene->shapes;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new_shape;
}

/**
 * @brief Clears a linked list of elements
 *
 * @note Could be expanded to take in a function pointer in case we need to
 * clear specific stuff inside of each node.
 */
void	clear_shapes(void *first)
{
	t_shape	*current;
	t_shape	*next;

	assert("First" && first);
	current = first;
	while (current)
	{
		printf("[!] Freeing shape %p\n", (void *)current);
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
	void	*tmp;

	assert("Scene" && scene);
	printf("======== Camera ========\n");
	print_camera(&scene->camera);
	printf("======== Ambient ========\n");
	print_ambient(&scene->ambient);
	printf("======== Lights ========\n");
	tmp = scene->lights;
	while (tmp)
	{
		print_light(tmp);
		tmp = ((t_light *)tmp)->next;
	}
	printf("======== Shapes ========\n");
	tmp = scene->shapes;
	while (tmp)
	{
		if (((t_shape *)tmp)->type == SPHERE)
			print_sphere(tmp);
		// else if (((t_shape *)tmp)->type == PLANE)
		// 	print_plane(tmp);
		// else if (((t_shape *)tmp)->type == CYLINDER)
		// 	print_cylinder(tmp);
		tmp = ((t_shape *)tmp)->next;
	}
}
