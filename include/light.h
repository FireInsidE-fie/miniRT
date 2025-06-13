#ifndef LIGHT_H
# define LIGHT_H

# include "point3.h"
# include "color.h"

typedef struct s_light
{
	t_point3		position;
	float			intensity;	// Range [0, 1.0]
	t_color			color;		// RGB color
	struct s_light	*next;
}	t_light;

#endif // LIGHT_H
