#include "parsing.h"
#include "scene.h"
#include "vector.h"
#include "minirt.h"
#include "utils.h"
#include "textures.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

void	compute_plane_light(t_vec3 *normal, t_point3 *intersect, t_color *color, t_result *result)
{
	*normal = result->closest->normal;
	if (result->closest->mat.texture == CHECKERBOARD)
		*color = apply_checker_plane(result->closest, intersect);
	else
		*color = result->closest->mat.color;
}

void	handle_plane_intersect(double t[2], t_shape *tmp, t_range range, t_result *result)
{
	(void)range;
	if (t[0] >= 0 && t[0] < result->closest_t)
	{
		result->closest = tmp;
		result->closest_t = t[0];
	}
}

/**
 *	Find out if we are hitting a plane with our ray.
 */
bool	hit_plane(t_point3 *origin, t_vec3 *dir, t_shape *plane, double *t)
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

void	print_plane(t_shape *plane)
{
	assert("Plane" && plane);
	assert("Shape type" && plane->type == PLANE);
	printf(
		"[!] - Plane\n"
		"Position: (%f, %f, %f)\n"
		"Normal: (%f, %f, %f)\n",
		plane->position.x, plane->position.y, plane->position.z,
		plane->normal.x, plane->normal.y, plane->normal.z
		);
	print_mat(&plane->mat);
}

int	create_plane(t_point3 *position, t_vec3 *normal, t_material *mat)
{
	t_shape		*plane;

	assert("Material" && mat->color.r >= 0.0f && mat->color.r <= 1.0f
		&& mat->color.g >= 0.0f && mat->color.g <= 1.0f
		&& mat->color.b >= 0.0f && mat->color.b <= 1.0f);
	plane = malloc(sizeof(t_shape));
	if (!plane)
		return (perror("miniRT (create_plane) - malloc"), MALLOC_ERR);
	vec_normalize(normal);
	plane->type = PLANE;
	plane->position = *position;
	plane->normal = *normal;
	plane->mat= *mat;
	plane->next = NULL;
	add_shape(plane);
	return (DONE);
}
