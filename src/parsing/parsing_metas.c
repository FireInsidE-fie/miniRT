#include "parsing.h"
#include "ambient.h"
#include "minirt.h"
#include "scene.h"
#include "libft.h"
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
	scene_ambient = &get_core()->scene.ambient;
	while (*line && ft_isalpha(*line))
		++line;
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	scene_ambient->intensity = ft_atof(line);
	if (scene_ambient->intensity < 0)
		return (VALUE_ERR);
	while (*line && (ft_isdigit(*line) || *line == '.'))
		++line;
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
	assert(line && "Line");
	printf("[!] - Parsing a camera...\n");
	return (0);
}

int	parse_light(char *line)
{
	assert(line && "Line");
	printf("[!] - Parsing a light...\n");
	return (0);
}
