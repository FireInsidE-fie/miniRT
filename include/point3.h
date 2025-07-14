#ifndef POINT3_H
# define POINT3_H

// Struct for a point in 3D space
typedef struct s_point3
{
	float	x;
	float	y;
	float	z;
}	t_point3;

// Vectors are also represented with a value for each of the coordinates
// Each value normalized to [0, 1] to represent magnitude
typedef t_point3	t_vec3;

// Functions //

t_point3	make_point3(float x, float y, float z);
t_vec3		point3_sub(t_point3 *a, t_point3 *b);
t_vec3		point3_scale(t_vec3 *v, double scalar);
t_point3	point3_invert(t_point3 *point);

#endif // POINT3_H
