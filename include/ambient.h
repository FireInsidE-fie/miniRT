/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:19:20 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:19:22 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

# include "material.h"

typedef struct s_ambient
{
	float	intensity;	// Range [0, 1.0]
	t_color	color;	// RGB color
}	t_ambient;

void	create_ambient(float intensity, t_color *color);
void	print_ambient(t_ambient *ambient);

#endif // AMBIENT_H
