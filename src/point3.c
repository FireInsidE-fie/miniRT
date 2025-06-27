#include "point3.h"

#include <assert.h>

t_point3	make_point3(float x, float y, float z)
{
	t_point3	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

/**
 * @brief Create a vector by subtracting two points in 3D space.
 */
t_vec3	point3_sub(t_point3 *a, t_point3 *b)
{
	t_vec3	vec;

	assert("A" && a);
	assert("B" && b);
	vec.x = a->x - b->x;
	vec.y = a->y - b->y;
	vec.z = a->z - b->z;
	return (vec);
}
