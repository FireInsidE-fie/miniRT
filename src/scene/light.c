#include "light.h"
#include "point3.h"
#include "scene.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>

int	create_light(t_point3 position, float intensity, t_color color)
{
	t_scene	*scene;
	t_light	*light;
	t_light	*tmp;

	light = malloc(sizeof(t_light));
	if (!light)
		return (perror("miniRT (create_light) - malloc"), 1);
	light->position = position;
	light->intensity = intensity;
	light->color = color;
	light->next = NULL;
	scene = get_scene();
	if (!scene->lights)
	{
		scene->lights = light;
		return (0);
	}
	tmp = scene->lights;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = light;
	return (0);
}

void	print_light(t_light *light)
{
	printf(
		"[!] - Light\n"
		"Position: (%f, %f, %f)"
		"\nIntensity: %f\n"
		"Color: (%f, %f, %f)\n",
		light->position.x, light->position.y, light->position.z,
		light->intensity,
		light->color.r, light->color.g, light->color.b
		);
}

float	get_light_intensity(t_point3 point, t_vec3 normal)
{
	t_scene	*scene;
	float	intensity = 0.0;
	t_light	*tmp;
	t_vec3	point_to_light;
	double	light_dot_normal;

	scene = get_scene();
	intensity += scene->ambient.intensity;
	tmp = scene->lights;
	while (tmp)
	{
		point_to_light = point3_sub(&tmp->position, &point);
		light_dot_normal = dot_product(&point_to_light, &normal);
		if (light_dot_normal > 0)
			intensity += tmp->intensity * light_dot_normal
				/ (vector_length(&normal) * vector_length(&point_to_light));
		tmp = tmp->next;
	}
	return (intensity);
}
