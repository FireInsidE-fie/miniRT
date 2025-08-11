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
	// printf("[!] - Parsing a meta element...\n");
	length = 0;
	while (ft_isalpha(line[length]))
		++length;
	if (length != META_ABBR_LENGTH)
		return (3);
	if (ft_strncmp(line, "A", META_ABBR_LENGTH) == 0)
		return parse_ambient(line);
	else if (ft_strncmp(line, "C", META_ABBR_LENGTH) == 0)
		return parse_camera(line);
	else if (ft_strncmp(line, "L", META_ABBR_LENGTH) == 0)
		return parse_light(line);
	return (3);
}

/**
 * @brief Parses a line containing a shape element (sphere, cylinder, plane...).
 */
static int	parse_shape(char *line)
{
	int	length;

	assert(line && "Line");
	// printf("[!] - Parsing a shape...\n");
	length = 0;
	while (ft_isalpha(line[length]))
		++length;
	if (length != SHAPE_ABBR_LENGTH)
		return (3);
	if (ft_strncmp(line, "sp", SHAPE_ABBR_LENGTH) == 0)
		return parse_sphere(line);
	else if (ft_strncmp(line, "cy", SHAPE_ABBR_LENGTH) == 0)
		return parse_cylinder(line);
	else if (ft_strncmp(line, "pl", SHAPE_ABBR_LENGTH) == 0)
		return parse_plane(line);
	return (3);
}

/**
 * @brief Checks for forbidden characters inside of a given .rt line.
 */
int	check_line(char *line)
{
	(void)line;
	//TODO
	return (0);
}

/**
 * @brief Parses a given .rt file and creates the scene from it.
 *
 * @details Error messages:
 * 0 - All went well
 * 1 - Path is not a .rt file
 * 2 - Failed to open the file
 * 3 - Abbreviation at start of line is wrong
 */
// TODO: make the above errors into macros evaluating to strings, so they can be printed when they occur (instead of just "error during parsing")
int	parse_scene(char *scene_path)
{
	int		scene_fd;
	int		status;
	char	*line;

	assert(scene_path && "Scene Path");
	printf("[!] - Beginning parsing...\n");
	scene_fd = open(scene_path, O_RDONLY);
	if (scene_fd == -1)
		return (perror("miniRT - parse_scene (open)"), 2);
	line = get_next_line(scene_fd);
	while (line)
	{
		write(1, line, ft_strlen(line));
		if (ft_isalpha(line[0]))
		{
			if (line[0] >= 'A' && line[0] <= 'Z')
				status = parse_meta(line);
			else
				status = parse_shape(line);
			if (status != 0)
				return (status);
		}
		line = get_next_line(scene_fd);
	}
	return (status);
}
