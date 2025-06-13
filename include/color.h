#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

// Struct for an RGB color representation //
typedef struct s_color
{
	float	r; // Value from 0 to 1
	float	g; // Value from 0 to 1
	float	b; // Value from 0 to 1
}	t_color;

// Functions //

t_color		make_color(float r, float g, float b);
uint32_t	color_to_int(t_color *color);

#endif // COLOR_H
