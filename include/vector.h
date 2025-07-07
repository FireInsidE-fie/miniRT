#ifndef VECTOR_H
# define VECTOR_H

# include "point3.h"

double	dot_product(t_vec3 *v1, t_vec3 *v2);
t_vec3	cross_product(t_vec3 *v1, t_vec3 *v2);
double	vector_length(t_vec3 *v);
void	vector_normalize(t_vec3 *v);
t_vec3	reflect_ray(t_vec3 *ray, t_vec3 *normal);

#endif // VECTOR_H
