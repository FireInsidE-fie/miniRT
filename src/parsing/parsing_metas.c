#include "parsing.h"
#include "ambient.h"
#include "minirt.h"
#include "scene.h"
#include "libft.h"

#include <assert.h>
#include <stdio.h>

int	parse_ambient(char *line)
{
	t_ambient	*scene_ambient;
	float		triad[3];

	assert(line && "Line");
	printf("[!] - Parsing an ambient...\n");
	scene_ambient = &get_core()->scene.ambient;
	while (*line && ft_isalpha(*line))
		++line;
	while (*line && (*line == ' ' || !ft_isprint(*line)))
		++line;
	if (!*line || *line == '\n')
		return (MISSING_ERR);
	scene_ambient->intensity = ft_atof(line);
	while (*line && (ft_isdigit(*line) || *line == '.'))
		++line;
	while (*line && (*line == ' ' || !ft_isprint(*line)))
		++line;
	if (!*line || *line == '\n')
		return (MISSING_ERR);
	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
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
