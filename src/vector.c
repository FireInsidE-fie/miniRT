#include "point3.h"
#include "math.h"

/**
 * @brief Returns the dot product of two vectors.
 */
double	dot_product(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

/**
 * @brief Returns the cross product of two vectors.
 */
t_vec3	cross_product(t_vec3 *v1, t_vec3 *v2)
{
	return (
		(t_vec3){
		v1->y * v2->z - v1->z * v2->y,
		v1->z * v2->x - v1->x * v2->z,
		v1->x * v2->y - v1->y * v2->x
	}
	);
}

/**
 * @brief Computes a vector's length: the square root of the dot product of that
 * vector with itself.
 */
double	vector_length(t_vec3 *v)
{
	return (sqrt(dot_product(v, v)));
}

/**
 * @brief Normalize a vector, or adapt it to a scale between 0 and 1
 * (unit length).
 */
void	vector_normalize(t_vec3 *v)
{
	double	length;

	length = vector_length(v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}
