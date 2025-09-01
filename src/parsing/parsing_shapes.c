#include "cylinder.h"
#include "plane.h"
#include "material.h"
#include "scene.h"
#include "sphere.h"
#include "parsing.h"
#include "utils.h"

#include <stdio.h>
#include <assert.h>
#include <unistd.h>

t_ps	parse_sphere(char *line)
{
	t_shape		tmp;
	t_ps		status;

	assert(line && "Line");
	printf("[!] - Parsing a sphere...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_position(line, &tmp.position);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	tmp.radius = ft_atof(line);
	if (tmp.radius < 0)
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	status = parse_material(line, &tmp.mat);
	if (status != 0)
		return (status);
	return (create_sphere(&tmp.position, tmp.radius, &tmp.mat));
}

t_ps	parse_cylinder(char *line)
{
	t_shape		tmp;
	t_ps		status;

	assert(line && "Line");
	printf("[!] - Parsing a cylinder...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_position(line, &tmp.position);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_position(line, &tmp.direction);
	if (!is_in_range(tmp.direction.x, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp.direction.y, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp.direction.x, (t_range){-1.0f, 1.0f}))
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	tmp.radius = ft_atof(line) / 2;
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	tmp.height = ft_atof(line);
	if (tmp.radius < 0.0f || tmp.height < 0.0f)
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	status = parse_material(line, &tmp.mat);
	if (status != DONE)
		return (status);
	create_cylinder(&tmp);
	return (0);
}

t_ps	parse_cone(char *line)
{
	t_shape		tmp;
	t_ps		status;

	assert(line && "Line");
	printf("[!] - Parsing a cylinder...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_position(line, &tmp.position);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_position(line, &tmp.direction);
	if (!is_in_range(tmp.direction.x, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp.direction.y, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp.direction.x, (t_range){-1.0f, 1.0f}))
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	tmp.radius = ft_atof(line) / 2;
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	tmp.height = ft_atof(line);
	if (tmp.radius < 0.0f || tmp.height < 0.0f)
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	status = parse_material(line, &tmp.mat);
	if (status != DONE)
		return (status);
	// create_cone(&tmp);
	return (0);
}

t_ps	parse_plane(char *line)
{
	t_shape		tmp;
	t_material	mat;

	assert(line && "Line");
	printf("[!] - Parsing a plane...\n");
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_position(line, &tmp.position);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_position(line, &tmp.direction);
	if (!is_in_range(tmp.direction.x, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp.direction.y, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp.direction.x, (t_range){-1.0f, 1.0f}))
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	parse_material(line, &mat);
	return (create_plane(&tmp.position, &tmp.direction, &mat));
}
