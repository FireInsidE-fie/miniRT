#include "point3.h"

/**
 * @brief Create a vector by subtracting two points in 3D space.
 */
t_vec3	point3_sub(t_point3 *a, t_point3 *b)
{
	t_vec3	vec;

	vec.x = a->x - b->x;
	vec.y = a->y - b->y;
	vec.z = a->z - b->z;
	return (vec);
}

t_point3	point3_add(t_point3 *a, t_vec3 *b)
{
	t_point3	result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}

/**
 * @brief Scale a vector or point by a scalar value.
 */
t_vec3	point3_scale(t_vec3 *v, double scalar)
{
	t_vec3	vec;

	vec.x = v->x * scalar;
	vec.y = v->y * scalar;
	vec.z = v->z * scalar;
	return (vec);
}

t_vec3	vec_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3	vec_scale(t_vec3 v, float scalar)
{
	return ((t_vec3){v.x * scalar, v.y * scalar, v.z * scalar});
}
