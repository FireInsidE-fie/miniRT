/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:29:53 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:29:54 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"
#include <stdlib.h>
#include <fcntl.h>

void	export_shapes(t_shape *shape, int fd)
{
	while (shape != NULL)
	{
		if (shape->type == SPHERE)
			export_sphere(shape, fd);
		else if (shape->type == PLANE)
			export_plane(shape, fd);
		else if (shape->type == CYLINDER)
			export_cylinder(shape, fd);
		else if (shape->type == CONE)
			export_cone(shape, fd);
		else if (shape->type == TRIANGLE)
			export_triangle(shape, fd);
		shape = shape->next;
	}
}

void	export_scene(void)
{
	int		fd;
	t_scene	*scene;
	t_light	*lights;
	t_shape	*shape;

	scene = get_scene();
	lights = scene->lights;
	shape = scene->shapes;
	fd = open("exported.rt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	export_meta(scene, lights, fd);
	export_shapes(shape, fd);
}
