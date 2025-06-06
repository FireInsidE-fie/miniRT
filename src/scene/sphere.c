#include "sphere.h"
#include "scene.h"

#include <stdlib.h>

/**
 * @brief Adds a new sphere element to the miniRT scene.
 *
 * @details This weird *tmp loop at the end of the function is a way to modify
 * the pointer contained in the `t_scene` for spheres, by taking a pointer on
 * that pointer, we can modify the first one easily.
 */
int	create_sphere(t_point3 position, double radius, t_color color)
{
	t_sphere	*sphere;
	t_sphere	**tmp;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (1);
	sphere->center = position;
	sphere->radius = radius;
	sphere->color = color;
	tmp = &get_scene()->spheres;
	while (*tmp)
		*tmp = (*tmp)->next;
	*tmp = sphere;
	return (0);
}

void	clear_spheres(void)
{
	t_scene		*scene;
	t_sphere	*current;
	t_sphere	*next;

	scene = get_scene();
	current = scene->spheres;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
