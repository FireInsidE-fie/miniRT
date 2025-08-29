#include "libft.h"
#include "material.h"
#include "parsing.h"
#include "point3.h"
#include "utils.h"

#include <assert.h>
#include <stdbool.h>

/**
 * @brief Parses a string as a number triad in the format X[.X],X[.XX],X[.XX].
 * Takes an array of 3 floats as argument to store the results.
 *
 * @details The brackets in the format denote optional parts.
 * @return 0 if all went well, 1 if a value was missing
 * or another error occurred.
 */
t_ps	parse_triad(char *str, float *result)
{
	assert(str && "String");
	assert(result && "Result array");
	while (*str && (*str != '-' && !ft_isdigit(*str)))
		++str;
	result[0] = ft_atof(str);
	while (*str
		&& (*str == '-' || *str == '+' || *str == '.' || ft_isdigit(*str)))
		++str;
	if (*(str++) != ',')
		return (TRIAD_ERR);
	result[1] = ft_atof(str);
	while (*str
		&& (*str == '-' || *str == '+' || *str == '.' || ft_isdigit(*str)))
		++str;
	if (*(str++) != ',')
		return (TRIAD_ERR);
	result[2] = ft_atof(str);
	return (DONE);
}

/**
 * @brief Parses a string as a triad of x, y and z values. Can be used for
 * both t_point3 and t_vec3 targets, since they are the same struct,
 * just renamed (aliased).
 */
t_ps	parse_position(char *line, t_point3 *result)
{
	float	triad[3];

	assert(line && "String");
	assert(result && "Result");
	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	result->x = triad[0];
	result->y = triad[1];
	result->z = triad[2];
	return (DONE);
}

static t_ps	parse_texture(char *line, t_texture *texture)
{
	int	i;

	i = 0;
	while (line[i] && ft_isalpha(line[i]))
		++i;
	if (i != TEXT_ABRR_LENGTH)
		return (VALUE_ERR);
	if (ft_strncmp(line, "NO", i) == 0)
		*texture = NONE;
	else if (ft_strncmp(line, "CH", i) == 0)
		*texture = CHECKERBOARD;
	else if (ft_strncmp(line, "EA", i) == 0)
		*texture = EARTH;
	else if (ft_strncmp(line, "MO", i) == 0)
		*texture = MOON;
	else
		return (VALUE_ERR);
	return (DONE);
}

/**
 * @brief Parses a material at the end of a .rt line into the pointer given
 * to it.
 */
t_ps	parse_material(char *line, t_material *mat)
{
	float	triad[3];

	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	if (!is_in_range(triad[0], (t_range){0, 255})
		|| !is_in_range(triad[1], (t_range){0, 255})
		|| !is_in_range(triad[2], (t_range){0, 255}))
		return (VALUE_ERR);
	mat->color.r = triad[0] / 255;
	mat->color.g = triad[1] / 255;
	mat->color.b = triad[2] / 255;
	if (goto_next_word(&line) != 0)
		return (MISSING_ERR);
	mat->specular = ft_atof(line);
	if (goto_next_word(&line) != 0)
		return (MISSING_ERR);
	mat->reflection = ft_atof(line);
	if (goto_next_word(&line) != 0)
	{
		mat->texture = NONE;
		return (DONE);					// Textures are optional
	}
	return (parse_texture(line, &mat->texture));
}

/**
 * @brief Goes to the next slice of data in a .rt line, skipping
 * over whitespace.
 * @details Uses a double pointer to be able to do pointer arithmetic on the
 * original line back in the parsing functions.
 */
t_ps	goto_next_word(char **line)
{
	while (**line && **line != '\n' && (ft_isprint(**line) && **line != ' '))
		++(*line);
	while (**line && **line != '\n' && (**line == ' ' || !ft_isprint(**line)))
		++(*line);
	if (!*line || **line == '\n')
		return (MISSING_ERR);
	return (DONE);
}
