#include "sphere.h"
#include "scene.h"

#include <stdlib.h>
#include <stdio.h>

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
		return (perror("miniRT (create_sphere) - malloc"), 1);
	sphere->center = position;
	sphere->radius = radius;
	sphere->color = color;
	sphere->next = NULL;
	tmp = &get_scene()->spheres;
	while (*tmp)
		*tmp = (*tmp)->next;
	*tmp = sphere;
	return (0);
}

void	print_sphere(t_sphere *sphere)
{
	printf(
		"[!] - Sphere\n"
		"Position: (%f, %f, %f)"
		"\nRadius: %f\n"
		"Color: (%f, %f, %f)\n",
		sphere->center.x, sphere->center.y, sphere->center.z,
		sphere->radius,
		sphere->color.r, sphere->color.g, sphere->color.b
		);
}
