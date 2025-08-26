#ifndef VECTOR_H
# define VECTOR_H

# include "point3.h"

double	dot_product(t_vec3 *v1, t_vec3 *v2);
t_vec3	cross_product(t_vec3 *v1, t_vec3 *v2);
double	vec_len(t_vec3 *v);
void	vec_normalize(t_vec3 *v);
double	vec_cos(t_vec3 *v1, t_vec3 *v2);

#endif // VECTOR_H
