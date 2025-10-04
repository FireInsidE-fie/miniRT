#include "scene.h"
#include "triangle.h"
#include "vector.h"
#include "parsing.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void	compute_triangle_light(t_vec3 *normal, t_color *color, t_result *result)
{
	*normal = result->closest->normal;
	*color = result->closest->mat.color;
}

void	handle_triangle_intersect(
	double t[2], t_shape *tri, t_result *result)
{
	if (t[0] >= 0 && t[0] < result->closest_t)
	{
		result->closest = tri;
		result->closest_t = t[0];
	}
}

/* Möller-Trumbore algorithm used for triangle hits

	checking if our ray has a hit-point on a given triangle.

	edge1/edge2 : define the triangle's plan, h is a perpendicular
	ray to the two edges. It's there to test if our ray is parallel
	to the triangle.

	det : when equal~ to 0, means the ray is parallel to the
	triangle's plan. (no intersect)

	inv_det : used to avoid repetitive divisions.
	(using multiplication instead of division cause it's lighter
	on the cpu).

	s : vector between "tra" and origin. helps to calculate the
	relative position of the intersect within the triangle. (cause
	a triangle has no pos).

	u/v : barycentric coordinates, if u or v < 0 OR u + v > 1,
	the hitpoint is outside the triangle. q helps to find v.

	t : intersect distance. Just like the other shapes, if
	t > 0.000001, it's a valid intersection.
*/

bool	hit_triangle(t_point3 *orig, t_vec3 *dir, t_shape *tri, double *t)
{
	t_trhit	hit;

	hit.edge1 = point3_sub(&tri->trb, &tri->tra);
	hit.edge2 = point3_sub(&tri->trc, &tri->tra);
	hit.h = cross_product(dir, &hit.edge2);
	hit.det = dot_product(&hit.edge1, &hit.h);
	if (fabs(hit.det) < 0.000001)
		return (false);
	hit.inv_det = 1.0 / hit.det;
	hit.s = point3_sub(orig, &tri->tra);
	hit.u = hit.inv_det * dot_product(&hit.s, &hit.h);
	if (hit.u < 0.0 || hit.u > 1.0)
		return (false);
	hit.q = cross_product(&hit.s, &hit.edge1);
	hit.v = hit.inv_det * dot_product(dir, &hit.q);
	if (hit.v < 0.0 || hit.u + hit.v > 1.0)
		return (false);
	*t = hit.inv_det * dot_product(&hit.edge2, &hit.q);
	return (*t > 0.000001);
}

int	create_triangle(t_point3 a, t_point3 b, t_point3 c, t_material mat)
{
	t_shape	*tri;
	t_vec3	edge1;
	t_vec3	edge2;

	tri = malloc(sizeof(t_shape));
	if (!tri)
		return (perror("miniRT (create_triangle) - malloc"), MALLOC_ERR);
	tri->type = TRIANGLE;
	tri->tra = a;
	tri->trb = b;
	tri->trc = c;
	tri->mat = mat;
	edge1 = point3_sub(&b, &a);
	edge2 = point3_sub(&c, &a);
	tri->normal = cross_product(&edge1, &edge2);
	vec_normalize(&tri->normal);
	tri->next = NULL;
	add_shape(tri);
	return (DONE);
}
