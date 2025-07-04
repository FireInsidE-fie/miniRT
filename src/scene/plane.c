#include "minirt.h"
#include "point3.h"
#include "vector.h"
#include "plane.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int	create_plane(t_point3 origin, t_vec3 normal, t_color color)
{
	t_scene	*scene;
	t_plane	*plane;
	t_plane	*tmp;

	assert("Color" && color.r >= 0.0f && color.r <= 1.0f
		&& color.g >= 0.0f && color.g <= 1.0f
		&& color.b >= 0.0f && color.b <= 1.0f);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (perror("miniRT (create_plane) - malloc"), 1);
	plane->origin = origin;
	plane->normal = normal;
	plane->color = color;
	plane->next = NULL;
	scene = &get_core()->scene;
	if (!scene->planes)
	{
		scene->planes = plane;
		return (0);
	}
	tmp = scene->planes;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = plane;
	return (0);
}

void	print_plane(t_plane *plane)
{
	assert("Plane" && plane);
	printf(
		"[!] - Plane\n"
		"Origin: (%f, %f, %f)\n"
		"Normal: (%f, %f, %f)\n"
		"Color: (%f, %f, %f)\n",
		plane->origin.x, plane->origin.y, plane->origin.z,
		plane->normal.x, plane->normal.y, plane->normal.z,
		plane->color.r, plane->color.g, plane->color.b
		);
}

bool	hit_plane(t_point3 *origin, t_vec3 *dir, t_plane *plane, double *t)
{
	t_vec3	po;

	assert("Origin" && origin);
	assert("Direction" && dir);
	assert("Plane" && plane);
	po = point3_sub(origin, &plane->origin);
	*t = dot_product(&po, &plane->normal) / dot_product(dir, &plane->normal);
	if (t)
		return (true);
	return (false);
}
