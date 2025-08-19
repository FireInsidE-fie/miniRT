#include "libft.h"
#include "material.h"
#include "parsing.h"
#include "utils.h"

#include <assert.h>
#include <stdbool.h>

float	ft_atof(char *str)
{
	float	result;

	assert(str && "String");
	result = ft_atoi(str);
	while (*str && (*str == '-' || ft_isdigit(*str)))
		++str;
	if (*str == '.')
		result += ft_atoi(++str) / 10.0f;
	return (result);
}

/**
 * @brief Parses a string as a number triad in the format X[.X],X[.XX],X[.XX].
 * Takes an array of 3 floats as argument to store the results.
 *
 * @details The brackets in the format denote optional parts.
 * @return 0 if all went well, 1 if a value was missing
 * or another error occurred.
 */
int	parse_triad(char *str, float *result)
{
	assert(str && "String");
	assert(result && "Result array");
	while (*str && (*str != '-' && !ft_isdigit(*str)))
		++str;
	result[0] = ft_atof(str);
	while (*str && (*str == '-' || *str == '+' || *str == '.' || ft_isdigit(*str)))
		++str;
	if (*(str++) != ',')
		return (1);
	result[1] = ft_atof(str);
	while (*str && (*str == '-' || *str == '+' || *str == '.' || ft_isdigit(*str)))
		++str;
	if (*(str++) != ',')
		return (1);
	result[2] = ft_atof(str);
	return (0);
}

/**
 * @brief Parses a material at the end of a .rt line into the pointer given
 * to it.
 */
int	parse_material(char *line, t_material *mat)
{
	float		triad[3];

	if (parse_triad(line, triad) != 0)
		return (TRIAD_ERR);
	if (!is_in_range(triad[0], (t_range){0, 255})
		|| !is_in_range(triad[1], (t_range){0, 255})
		|| !is_in_range(triad[2], (t_range){0, 255}))
		return (VALUE_ERR);
	mat->color.r = triad[0] / 255;
	mat->color.g = triad[1] / 255;
	mat->color.b = triad[2] / 255;
	mat->specular = 1000; // TODO
	mat->reflection = 0.2; // TODO
	return (0);
}

/**
 * @brief Goes to the next slice of data in a .rt line, skipping
 * over whitespace.
 * @details Uses a double pointer to be able to do pointer arithmetic on the
 * original line back in the parsing functions.
 */
int	goto_next_word(char **line)
{
	while (**line && (ft_isprint(**line) && **line != ' '))
		++(*line);
	while (**line && (**line == ' ' || !ft_isprint(**line)))
		++(*line);
	if (!*line || **line == '\n')
		return (MISSING_ERR);
	return (0);
}
