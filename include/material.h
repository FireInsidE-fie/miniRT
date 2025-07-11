#ifndef MATERIAL_H
# define MATERIAL_H

# include <stdint.h>

# define SKY_COLOR {0.2, 0.2, 0.2}

// Struct for an RGB color representation //
typedef struct s_color
{
	float	r;		// Value from 0 to 1
	float	g;		// Value from 0 to 1
	float	b;		// Value from 0 to 1
}	t_color;

// Struct to represent an shape's material
typedef struct s_material
{
	t_color	color;
	float	specular;
	float	reflection;
}	t_material;

// Functions //

t_color		make_color(float r, float g, float b);
uint32_t	color_to_int(t_color *color);
t_material	make_material(t_color color, float specular, float reflection);

#endif // MATERIAL_H
