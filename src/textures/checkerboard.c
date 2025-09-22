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

/*	Per pixel/light check, given an uv point, return
*	a black t_color if the result is odd.
*	the size of the checkerboard pattern can be changed.
*	
*	the size is the (* 10) in this case.
*/
t_color	apply_checker_sphere(t_shape *sphere, t_uv uv)
{
	int		x;
	int		y;

	x = (int)(uv.u * 10);
	y = (int)(uv.v * 10);
	if ((x + y) % 2 == 0)
		return (sphere->mat.color); // t_color
	else
		return ((t_color){0, 0, 0}); // Black
}

/*	Per pixel/light check, given an x and z point, return
*	a black t_color if the result is odd.
*	the size of the checkerboard pattern can be changed.
*	
*	The floor() function rounds a number DOWN to the nearest
*	integer (but as double). -5.1 becomes -6.0 and 5.1 becomes 5.0
*
*	Since we are working with x and z coords, a vertical
*	plane would look striped instead of checkered.
*	the size is the (/ 10) in this case.
*/
t_color	apply_checker_plane(t_shape *plane, t_point3 *point)
{
	int	x;
	int	y;

	x = (int)floor(point->x / 10);
	y = (int)floor(point->z / 10);
	if ((x + y) % 2 == 0)
		return (plane->mat.color); // t_color
	else
		return ((t_color){0, 0, 0}); // Black
}
