#include "cylinder.h"
#include "cone.h"
#include "plane.h"
#include "material.h"
#include "scene.h"
#include "sphere.h"
#include "parsing.h"
#include "utils.h"

#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Parses both a triad of position and a triad of direction, checking
 * the latter for the range [-1, 1].
 */
t_ps	parse_pos_dir(char **line, t_shape *tmp)
{
	if (goto_next_word(line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(*line, &tmp->position) != DONE)
		return (TRIAD_ERR);
	if (goto_next_word(line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(*line, &tmp->direction) != DONE)
		return (TRIAD_ERR);
	if (!is_in_range(tmp->direction.x, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp->direction.y, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp->direction.x, (t_range){-1.0f, 1.0f}))
		return (VALUE_ERR);
	return (DONE);
}

t_ps	parse_sphere(char *line)
{
	t_shape		tmp;
	t_ps		status;

	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	status = parse_position(line, &tmp.position);
	if (status != DONE)
		return (status);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	tmp.radius = ft_atof(line) / 2;
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

	status = parse_pos_dir(&line, &tmp);
	if (status != DONE)
		return (status);
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
	return (create_cylinder(&tmp));
}

t_ps	parse_cone(char *line)
{
	t_shape		tmp;
	t_ps		status;

	status = parse_pos_dir(&line, &tmp);
	if (status != DONE)
		return (status);
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
	return (create_cone(&tmp), 0);
}

t_ps	parse_plane(char *line)
{
	t_shape		tmp;
	t_material	mat;
	t_ps		status;

	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(line, &tmp.position) != DONE)
		return (TRIAD_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(line, &tmp.direction) != DONE)
		return (TRIAD_ERR);
	if (!is_in_range(tmp.direction.x, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp.direction.y, (t_range){-1.0f, 1.0f})
		|| !is_in_range(tmp.direction.x, (t_range){-1.0f, 1.0f}))
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	status = parse_material(line, &mat);
	if (status != DONE)
		return (status);
	return (create_plane(&tmp.position, &tmp.direction, &mat));
}
