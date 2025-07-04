#ifndef PLANE_H
# define PLANE_H

# include "point3.h"
# include "color.h"

typedef struct s_plane
{
	t_point3		origin;
	t_vec3			normal;
	t_color			color;
	struct s_plane	*next;
}	t_plane;

int		create_plane(t_point3 origin, t_vec3 normal, t_color color);
void	print_plane(t_plane *plane);

#endif // PLANE_H
