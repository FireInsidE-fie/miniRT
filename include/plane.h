/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:17 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:20:23 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "point3.h"
# include "minirt.h"
# include "scene.h"
# include <stdbool.h>

void	compute_plane_light(t_vec3 *normal,
			t_point3 *intersect,
			t_color *color,
			t_result *result);
void	handle_plane_intersect(double t[2], t_shape *tmp, t_result *result);
int		create_plane(t_point3 *position, t_vec3 *normal, t_material *mat);
void	print_plane(t_shape *plane);
bool	hit_plane(t_point3 *origin, t_vec3 *dir, t_shape *plane, double *t);

#endif
