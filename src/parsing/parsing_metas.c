#include "light.h"
#include "material.h"
#include "parsing.h"
#include "ambient.h"
#include "scene.h"
#include "utils.h"

#include <threads.h>  // TODO: huh???

t_ps	parse_ambient(char *line)
{
	t_ambient	*scene_ambient;
	float		triad[3];

	scene_ambient = &get_scene()->ambient;
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	scene_ambient->intensity = ft_atof(line);
	if (scene_ambient->intensity < 0.0f || scene_ambient->intensity > 1.0f)
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

t_ps	parse_camera(char *line)
{
	t_point3	pos;
	t_vec3		dir;
	float		fov;

	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(line, &pos) != DONE)
		return (TRIAD_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(line, &dir) != DONE)
		return (TRIAD_ERR);
	if (!is_in_range(dir.x, (t_range){-1.0f, 1.0f})
		|| !is_in_range(dir.y, (t_range){-1.0f, 1.0f})
		|| !is_in_range(dir.z, (t_range){-1.0f, 1.0f}))
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	fov = ft_atof(line);
	if (fov < 0.0f || fov > 180.0f)
		return (VALUE_ERR);
	create_camera(&pos, &dir, fov);
	return (0);
}

t_ps	parse_light(char *line)
{
	t_light		tmp;
	float		triad[3];

	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_position(line, &tmp.position) != DONE)
		return (TRIAD_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	tmp.intensity = ft_atof(line);
	if (!is_in_range(tmp.intensity, (t_range){0.0f, 1.0f}))
		return (VALUE_ERR);
	if (goto_next_word(&line) == MISSING_ERR)
		return (MISSING_ERR);
	if (parse_triad(line, triad))
		return (TRIAD_ERR);
	tmp.color.r = triad[0] / 255;
	tmp.color.g = triad[1] / 255;
	tmp.color.b = triad[2] / 255;
	if (!is_in_range(tmp.color.r, (t_range){0.0f, 1.0f})
		|| !is_in_range(tmp.color.g, (t_range){0.0f, 1.0f})
		|| !is_in_range(tmp.color.b, (t_range){0.0f, 1.0f}))
		return (VALUE_ERR);
	return (create_light(&tmp.position, tmp.intensity, &tmp.color));
}
