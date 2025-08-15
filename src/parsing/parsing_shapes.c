#include "material.h"
#include "sphere.h"
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
	int			status;

	assert(line && "Line");
	printf("[!] - Parsing a sphere...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	position.x = triad[0];		// TODO: parse_pos() to reduce redundant code
	position.y = triad[1];
	position.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	radius = ft_atof(line);
	if (radius < 0)
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	status = parse_material(line, &mat);
	if (status != 0)
		return (status);
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
