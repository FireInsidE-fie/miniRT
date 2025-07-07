#ifndef MATERIAL_H
# define MATERIAL_H

# include "color.h"

// A texture material
typedef struct s_material
{
	t_color			color;
	float			reflective;
}	t_material;

#endif // MATERIAL_H
