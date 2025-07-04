#ifndef PLANE_H
# define PLANE_H

# include "point3.h"
# include "color.h"

# include <stdbool.h>

typedef struct s_plane
{
	t_point3		origin;
	t_vec3			normal;
	t_color			color;
	struct s_plane	*next;
}	t_plane;

int		create_plane(t_point3 origin, t_vec3 normal, t_color color);
bool	hit_plane(t_point3 *origin, t_vec3 *dir, t_plane *plane, double *t);
void	print_plane(t_plane *plane);

#endif // PLANE_H
