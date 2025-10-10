/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:20:00 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:20:01 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include <stdint.h>
# include "texturedata.h"

# ifndef SKY_COLOR
#  define SKY_COLOR 0.0
# endif  // SKY_COLOR

// Enum for representing which texture is being used
typedef enum e_texture
{
	NONE,
	CHECKERBOARD,
	EARTH,			// Only for spheres
	MOON,			// Only for spheres
}	t_texture;

// Struct for an RGB color representation
typedef struct s_color
{
	float	r;		// Value from 0 to 1
	float	g;		// Value from 0 to 1
	float	b;		// Value from 0 to 1
}	t_color;

// Struct to represent an shape's material
typedef struct s_material
{
	t_color			color;
	float			specular;
	float			reflection;
	t_texture		texture;
	t_texturedata	texturedata;
}	t_material;

// Functions //

t_color		color_mult(t_color c, float factor);
t_color		color_add(t_color a, t_color b);
uint32_t	color_to_int(t_color *color);
void		print_mat(t_material *mat);

#endif // MATERIAL_H
