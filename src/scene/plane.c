#include "sphere.h"
#include "scene.h"
#include "vector.h"
#include "minirt.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

bool hit_plane(t_point3 *origin, t_vec3 *dir, t_shape *plane, double *t)
{
	double	denom;
	t_vec3	origin_to_plane;
	
	denom = dot_product(&plane->normal, dir);

	if (fabs(denom) > 1e-6) // floatabsolute over 0.000001 or 10^-6
	{
		origin_to_plane = point3_sub(&plane->position, origin);
		*t = dot_product(&origin_to_plane, &plane->normal) / denom;
		return (*t >= 0);
	}
	return false;
}

int	create_plane(t_point3 position, t_vec3 normal, t_material mat)
{
	t_shape		*plane;

	assert("Material" && mat.color.r >= 0.0f && mat.color.r <= 1.0f
		&& mat.color.g >= 0.0f && mat.color.g <= 1.0f
		&& mat.color.b >= 0.0f && mat.color.b <= 1.0f);
	plane = malloc(sizeof(t_shape));
	if (!plane)
		return (perror("miniRT (create_plane) - malloc"), 1);
	plane->type = PLANE;
	plane->position = position;
    plane->normal = normal;
	plane->mat= mat;
	plane->next = NULL;
	add_shape(plane);
	return (0);
}
