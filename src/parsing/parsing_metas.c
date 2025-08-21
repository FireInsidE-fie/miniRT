#include "light.h"
#include "material.h"
#include "parsing.h"
#include "ambient.h"
#include "point3.h"
#include "scene.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <threads.h>

int	parse_ambient(char *line)
{
	t_ambient	*scene_ambient;
	float		triad[3];

	assert(line && "Line");
	printf("[!] - Parsing an ambient...\n");
	scene_ambient = &get_scene()->ambient;
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	scene_ambient->intensity = ft_atof(line);
	if (scene_ambient->intensity < 0)
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	if (!is_in_range(triad[0], (t_range){0, 255})
		|| !is_in_range(triad[1], (t_range){0, 255})
		|| !is_in_range(triad[2], (t_range){0, 255}))
		return (VALUE_ERR);
	scene_ambient->color.r = triad[0] / 255;
	scene_ambient->color.g = triad[1] / 255;
	scene_ambient->color.b = triad[2] / 255;
	return (0);
}

int	parse_camera(char *line)
{
	t_camera	*scene_camera;
	float		triad[3];

	assert(line && "Line");
	printf("[!] - Parsing a camera...\n");
	scene_camera = &get_scene()->camera;
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad))
		return (TRIAD_ERR);
	scene_camera->position.x = triad[0];
	scene_camera->position.y = triad[1];
	scene_camera->position.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad))
		return (TRIAD_ERR);
	scene_camera->direction.x = triad[0];
	scene_camera->direction.y = triad[1];
	scene_camera->direction.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	scene_camera->fov = ft_atof(line);
	if (scene_camera->fov < 0)
		return (VALUE_ERR);
	return (0);
}

int	parse_light(char *line)
{
	t_point3	position;
	float		intensity;
	t_color		color;
	float		triad[3];

	assert(line && "Line");
	printf("[!] - Parsing a light...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad))
		return (TRIAD_ERR);
	position.x = triad[0];
	position.y = triad[1];
	position.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	intensity = ft_atof(line);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad))
		return (TRIAD_ERR);
	color.r = triad[0] / 255;
	color.g = triad[1] / 255;
	color.b = triad[2] / 255;
	if (!is_in_range(color.r, (t_range){0.0f, 1.0f})
		|| !is_in_range(color.g, (t_range){0.0f, 1.0f})
		|| !is_in_range(color.b, (t_range){0.0f, 1.0f}))
		return (VALUE_ERR);
	create_light(position, intensity, color);
	return (0);
}
