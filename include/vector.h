#ifndef VECTOR_H
# define VECTOR_H

// Struct for a point in 3D space
typedef struct s_point3
{
	double	x;
	double	y;
	double	z;
}	t_point3;

// Vectors are also represented with a value for each of the coordinates
// Each value normalized to [0, 1] to represent magnitude
typedef t_point3	t_vec3;

#endif // VECTOR_H
