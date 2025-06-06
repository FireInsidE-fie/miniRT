#ifndef AMBIENT_H
# define AMBIENT_H

# include "color.h"

typedef struct s_ambient
{
	double	ratio;	// Range [0, 1.0]
	t_color	color;	// RGB color
}	t_ambient;

#endif // AMBIENT_H
