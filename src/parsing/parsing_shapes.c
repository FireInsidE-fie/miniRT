#include "material.h"
#include "sphere.h"
#include "utils.h"
#include "parsing.h"
#include "point3.h"

#include <stdio.h>
#include <assert.h>
#include <unistd.h>

int	parse_sphere(char *line)
{
	t_point3	position;
	float		radius;
	t_material	mat;
	float		triad[3];

	assert(line && "Line");
	printf("[!] - Parsing a sphere...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad) != 0)
		return (printf("1\n"), TRIAD_ERR);
	position.x = triad[0];
	position.y = triad[1];
	position.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	radius = ft_atof(line);
	if (radius < 0)
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	printf("[!] - %s\n", line);
	if (parse_triad(line, triad) != 0)
		return (printf("2\n"), TRIAD_ERR);
	if (!is_in_range(triad[0], (t_range){0, 255})
		|| !is_in_range(triad[1], (t_range){0, 255})
		|| !is_in_range(triad[2], (t_range){0, 255}))
		return (VALUE_ERR);
	mat.color.r = triad[0] / 255;
	mat.color.g = triad[1] / 255;
	mat.color.b = triad[2] / 255;
	mat.specular = 0.2; // TODO
	mat.reflection = 1000; // TODO
	create_sphere(position, radius, mat);
	return (0);
}

int	parse_cylinder(char *line)
{
	assert(line && "Line");
	printf("[!] - Parsing a cylinder...\n");
	return (0);
}

int	parse_plane(char *line)
{
	assert(line && "Line");
	printf("[!] - Parsing a plane...\n");
	return (0);
}
