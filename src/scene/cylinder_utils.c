/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:25:23 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:26:37 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "scene.h"
#include "minirt.h"

t_vec3	get_cylinder_normal(t_shape *cyl, t_point3 *intersect)
{
	t_vec3		base_to_p;
	t_vec3		proj;
	t_vec3		normal;
	double		axis_height;

	base_to_p = point3_sub(intersect, &cyl->position);
	axis_height = dot_product(&base_to_p, &cyl->direction);
	proj = point3_scale(&cyl->direction, axis_height);
	normal = point3_sub(&base_to_p, &proj);
	vec_normalize(&normal);
	return (normal);
}

void	compute_cylinder_light(t_vec3 *normal, t_point3 *intersect,
								t_color *color, t_result *result)
{
	t_shape	*cyl;

	cyl = result->closest;
	*normal = get_cylinder_normal(cyl, intersect);
	*color = cyl->mat.color;
}

void	handle_cylinder_intersect(double t[2], t_shape *cyl, t_result *result)
{
	if (t[0] >= 0 && t[0] < result->closest_t)
	{
		result->closest = cyl;
		result->closest_t = t[0];
	}
	if (t[1] >= 0 && t[1] < result->closest_t)
	{
		result->closest = cyl;
		result->closest_t = t[1];
	}
}

/**
 * @brief Projects a supposedly normalized vector "v" on a "u" axis
 */
t_vec3	project_vec(t_vec3 *v, t_vec3 *axis)
{
	t_vec3	proj;
	double	dot;

	dot = dot_product(v, axis);
	proj = point3_scale(axis, dot);
	return (proj);
}
