/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:51 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:20:52 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "point3.h"

double	dot_product(t_vec3 *v1, t_vec3 *v2);
t_vec3	cross_product(t_vec3 *v1, t_vec3 *v2);
double	vec_len(t_vec3 *v);
void	vec_normalize(t_vec3 *v);

#endif // VECTOR_H
