/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:40 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:19:41 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "point3.h"
# include "minirt.h"
# include "scene.h"

# include <stdbool.h>

// Main cylinder functions - cylinder.c
bool	hit_cylinder(t_point3 *origin, t_vec3 *dir, t_shape *cyl, double *t);
void	print_cylinder(t_shape *cylinder);
int		create_cylinder(t_shape *tmp);

// Cylinder utils - cylinder_utils.c
t_vec3	get_cylinder_normal(t_shape *cyl, t_point3 *intersect);
void	compute_cylinder_light(
			t_vec3 *normal, t_point3 *intersect,
			t_color *color, t_result *result);
void	handle_cylinder_intersect(
			double t[2], t_shape *cyl, t_result *result);
t_vec3	project_vec(t_vec3 *v, t_vec3 *axis);

#endif
