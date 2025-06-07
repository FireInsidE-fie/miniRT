#ifndef COLOR_H
# define COLOR_H

// Struct for an RGB color representation //
typedef struct s_color
{
	double	r; // Value from 0 to 1
	double	g; // Value from 0 to 1
	double	b; // Value from 0 to 1
}	t_color;

// Functions //

t_color	make_color(double r, double g, double b);

#endif // COLOR_H
