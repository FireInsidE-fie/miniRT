/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:25:52 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:26:37 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "scene.h"
#include "material.h"

#include <stdbool.h>
#include <math.h>

// Number of checkerboard squares in a shape's width (defines a square's size)
#define CHECKERBOARD_SIZE 10

/*
 * @brief Per pixel/light check, given an uv point, return
 * a black t_color if the result is odd.
*/
t_color	apply_checker_sphere(t_shape *sphere, t_uv uv)
{
	int	x;
	int	y;

	x = (int)(uv.u * CHECKERBOARD_SIZE);
	y = (int)(uv.v * CHECKERBOARD_SIZE);
	if ((x + y) % 2 == 0)
		return (sphere->mat.color);
	else
		return ((t_color){0, 0, 0});
}

/*
 * @brief Per pixel/light check, given an x and z point, return
 * a black t_color if the result is odd.
 *
 * @details
 * The floor() function rounds a number DOWN to the nearest
 * integer (but as double). -5.1 becomes -6.0 and 5.1 becomes 5.0
 * Since we are working with x and z coords, a vertical
 * plane would look striped instead of checkered.
*/
t_color	apply_checker_plane(t_shape *plane, t_point3 *point)
{
	int	x;
	int	y;

	x = (int)floor(point->x / CHECKERBOARD_SIZE);
	y = (int)floor(point->z / CHECKERBOARD_SIZE);
	if ((x + y) % 2 == 0)
		return (plane->mat.color);
	else
		return ((t_color){0, 0, 0});
}
