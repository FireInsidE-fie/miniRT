#include "sphere.h"
#include "textures.h"
#include "parsing.h"
#include "scene.h"
#include "vector.h"
#include "minirt.h"
#include "material.h"
#include "mlx.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Swap out 10 for any other scale

t_color	apply_checker_sphere(t_shape *sphere, t_uv uv)
{
	int		x;
	int		y;

	x = (int)(uv.u * 10);
	y = (int)(uv.v * 10);

	if ((x + y) % 2 == 0)
		return (sphere->mat.color); // t_color
	else
		return (t_color){0, 0, 0}; // Black
}

t_color	apply_checker_plane(t_shape *plane, t_point3 *point)
{
	int x;
	int y;

	x = (int)floor(point->x / 10);
	y = (int)floor(point->z / 10);

	if ((x + y) % 2 == 0)
		return (plane->mat.color); // t_color
	else
		return (t_color){0, 0, 0}; // Black
}