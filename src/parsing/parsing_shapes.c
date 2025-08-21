#include "cylinder.h"
#include "plane.h"
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
	if (!create_sphere(position, radius, mat))
		return (MALLOC_ERR);
	return (0);
}

// TODO: remake all parsing functions to use a temp element instead of individual variables, this is way too long
int	parse_cylinder(char *line)
{
	t_point3	position;
	t_vec3		direction;
	float		radius;
	float		height;
	t_material	mat;
	float		triad[3];
	int			status;

	assert(line && "Line");
	printf("[!] - Parsing a cylinder...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	position.x = triad[0];
	position.y = triad[1];
	position.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	direction.x = triad[0];
	direction.y = triad[1];
	direction.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	radius = ft_atof(line) / 2;
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	height = ft_atof(line);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (radius < 0.0f || height < 0.0f)
		return (VALUE_ERR);
	status = parse_material(line, &mat);
	if (status != DONE)
		return (status);
	create_cylinder(position, direction, radius, height, mat);
	return (0);
}

int	parse_plane(char *line)
{
	t_point3	position;
	t_vec3		normal;
	t_material	mat;
	float		triad[3];

	assert(line && "Line");
	printf("[!] - Parsing a plane...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	position.x = triad[0];
	position.y = triad[1];
	position.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	normal.x = triad[0];
	normal.y = triad[1];
	normal.z = triad[2];
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_material(line, &mat);
	create_plane(position, normal, mat);
	return (0);
}
