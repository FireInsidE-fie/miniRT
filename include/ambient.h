#ifndef AMBIENT_H
# define AMBIENT_H

# include "color.h"

typedef struct s_ambient
{
	float	intensity;	// Range [0, 1.0]
	t_color	color;	// RGB color
}	t_ambient;

void	create_ambient(float intensity, t_color color);

#endif // AMBIENT_H
