#include "libft.h"
#include "parsing.h"

#include <assert.h>
#include <stdbool.h>
// #include <stdio.h>

float	ft_atof(char *str)
{
	float	result;

	assert(str && "String");
	result = ft_atoi(str);
	while (*str && (*str == '-' || ft_isdigit(*str)))
		++str;
	if (*str == '.')
		result += ft_atoi(++str) / 10.0f;
	// printf("[!] - ft_atof gave %.2f back!\n", result);
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
 * @brief Goes to the next slice of data in a .rt line, skipping
 * over whitespace.
 * @details Uses a double pointer to be able to do pointer arithmetic on the
 * original line back in the parsing functions.
 */
int	goto_next_word(char **line)
{
	while (**line && (**line == ' ' || !ft_isprint(**line)))
		++(*line);
	if (!*line || **line == '\n')
		return (MISSING_ERR);
	return (0);
}
