#include "point3.h"

/**
 * @brief Returns the dot product of two vectors.
 */
double	dot_product(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/**
 * @brief Returns the cross product of two vectors.
 */
t_vec3	cross_product(t_vec3 v1, t_vec3 v2)
{
	return (
		(t_vec3){
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	}
	);
}
