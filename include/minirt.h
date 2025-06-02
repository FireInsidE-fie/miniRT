#ifndef MINIRT_H
# define MINIRT_H

// Struct for a point in 3D space //
typedef struct s_point3
{
	double	x;
	double	y;
	double	z;
}	t_point3;

// Vectors are also represented with a value for each of the coordinates //
typedef t_point3	t_vector3;

#endif //MINIRT_H
