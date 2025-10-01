#include "light.h"
#include "material.h"
#include "parsing.h"
#include "point3.h"
#include "scene.h"

#include <stdlib.h>
#include <stdio.h>

void	clear_lights(void *first)
{
	t_light	*current;
	t_light	*next;

	if (!first)
		return ;
	current = first;
	while (current)
	{
		printf("[!] - Freeing light %p\n", (void *)current);
		next = current->next;
		free(current);
		current = next;
	}
}

int	create_light(t_point3 *position, float intensity, t_color *color)
{
	t_scene	*scene;
	t_light	*light;
	t_light	*tmp;

	light = malloc(sizeof(t_light));
	if (!light)
		return (perror("miniRT (create_light) - malloc"), MALLOC_ERR);
	light->position = *position;
	light->intensity = intensity;
	light->color = *color;
	light->next = NULL;
	scene = get_scene();
	if (!scene->lights)
	{
		scene->lights = light;
		return (DONE);
	}
	tmp = scene->lights;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = light;
	return (DONE);
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
