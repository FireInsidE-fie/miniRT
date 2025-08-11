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

	assert(line && "Line");
	printf("[!] - Parsing an ambient...\n");
	scene_ambient = &get_core()->scene.ambient;
	while (*line && ft_isalpha(*line))
		++line;
	while (*line && (*line == ' ' || !ft_isprint(*line)))
		++line;
	scene_ambient->intensity = ft_atof(line);
	while (*line && (*line == ' ' || !ft_isprint(*line)))
		++line;
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
