#include "parsing.h"
#include "get_next_line.h"
#include "libft.h"
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Parses a line containing a meta element (lightning, camera).
 */
static int	parse_meta(char *line)
{
	int	length;

	assert(line && "Line");
	length = 0;
	while (ft_isalpha(line[length]))
		++length;
	if (length != META_ABBR_LENGTH)
		return (TYPE_ERR);
	if (ft_strncmp(line, "A", META_ABBR_LENGTH) == 0)
		return (parse_ambient(line));
	else if (ft_strncmp(line, "C", META_ABBR_LENGTH) == 0)
		return (parse_camera(line));
	else if (ft_strncmp(line, "L", META_ABBR_LENGTH) == 0)
		return (parse_light(line));
	return (TYPE_ERR);
}

/**
 * @brief Parses a line containing a shape element (sphere, cylinder, plane...).
 */
static int	parse_shape(char *line)
{
	int	length;

	assert(line && "Line");
	length = 0;
	while (ft_isalpha(line[length]))
		++length;
	if (length != SHAPE_ABBR_LENGTH)
		return (TYPE_ERR);
	if (ft_strncmp(line, "sp", SHAPE_ABBR_LENGTH) == 0)
		return (parse_sphere(line));
	else if (ft_strncmp(line, "cy", SHAPE_ABBR_LENGTH) == 0)
		return (parse_cylinder(line));
	else if (ft_strncmp(line, "pl", SHAPE_ABBR_LENGTH) == 0)
		return (parse_plane(line));
	return (TYPE_ERR);
}

/**
 * @brief Checks for forbidden characters inside of a given .rt line.
 * @details letters only on the first word after that, only numbers and .,-+
 */
static int	check_line(char *line)
{
	if (ft_isprint(*line) && *line != ' ' && !ft_isalpha(*line))
		return (CHAR_ERR);
	while (*line && !ft_isalpha(*line) && *line != '\n')
		++line;
	if (!*line || *line == '\n')
		return (0);
	while (*line && ft_isalpha(*line))
		++line;
	if (ft_isprint(*line) && *line != ' ')
		return (printf("[!] - 1\n"), CHAR_ERR);
	while (*line && *line != '\n')
	{
		if (ft_isprint(*line) && *line != ' '
			&& *line != '.' && *line != ',' && *line != '-' && *line != '+'
			&& !ft_isdigit(*line))
			return (printf("[!] - 2\n"), CHAR_ERR);
		++line;
	}
	return (0);
}

/**
 * @brief Prints the parsing status after it is done or an error occurred.
 */
static int	print_ps(t_parsing_status status, int line_n)
{
	if (status == DONE)
		printf("[!] - Done parsing scene!\n");
	else if (status == FILE_ERR)
		printf("[!] - Path doesn't end in .rt!\n");
	else if (status == OPEN_ERR)
		printf("[!] - Failed to open scene file!\n");
	else if (status == TYPE_ERR)
		printf("[!] - Line %d - Wrong abbreviation found "
			"at start of line!\n", line_n);
	else if (status == TRIAD_ERR)
		printf("[!] - Line %d - Error while parsing a triad of numbers!\n"
			"Remember to use format 'x[.x],x[.x],x[.x]'.\n"
			"Parts in [] are optional.\n", line_n);
	else if (status == CHAR_ERR)
		printf("[!] - Line %d - A character that shouldn't be "
			"there was found!\n", line_n);
	else if (status == MISSING_ERR)
		printf("[!] - Line %d - A value for this object is missing!\n", line_n);
	else if (status == VALUE_ERR)
		printf("[!] - Line %d - A value was incorrect!\n"
			"This can range from negative color values to too "
			"big / too small numbers.\n", line_n);
	else if (status == MALLOC_ERR)
		printf("[!] - Line %d - malloc error!\n", line_n);
	return (status);
}

/**
 * @brief Parses a given .rt file and creates the scene from it.
 */
// TODO: print accurate error messages depending on the error macro
int	parse_scene(char *scene_path)
{
	int		scene_fd;
	int		status;
	char	*line;
	int		line_n;

	assert(scene_path && "Scene Path");
	printf("[!] - Beginning parsing...\n");
	// TODO: check if path ends with .rt
	scene_fd = open(scene_path, O_RDONLY);
	if (scene_fd == -1)
		return (perror("miniRT - parse_scene (open)"), print_ps(FILE_ERR, 0));
	line = get_next_line(scene_fd);
	line_n = 1;
	while (line)
	{
		write(1, line, ft_strlen(line));		// debug
		status = check_line(line);
		if (status != DONE)
			break ;
		if (ft_isalpha(line[0]))
		{
			if (line[0] >= 'A' && line[0] <= 'Z')
				status = parse_meta(line);
			else
				status = parse_shape(line);
			if (status != DONE)
				break ;
		}
		free(line);
		line = get_next_line(scene_fd);
		++line_n;
	}
	if (status != DONE)
		get_next_line(-1);	// To clean gnl stash
	return (close(scene_fd), free(line), print_ps(status, line_n));
}
