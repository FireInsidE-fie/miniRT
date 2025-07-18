#ifndef LIGHT_H
# define LIGHT_H

# include "point3.h"
# include "material.h"

typedef struct s_light
{
	t_point3		position;
	float			intensity;	// Range [0, 1.0]
	t_color			color;		// RGB color
	struct s_light	*next;
}	t_light;

int		create_light(t_point3 position, float intensity, t_color color);
void	clear_lights(void *first);
void	print_light(t_light *light);
t_vec3	reflect_ray(t_vec3 *ray, t_vec3 *normal);
float	get_light_intensity(t_point3 *point, t_vec3 *normal, int specular);

#endif // LIGHT_H
