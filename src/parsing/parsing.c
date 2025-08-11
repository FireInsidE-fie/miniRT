#include "get_next_line.h"
#include "libft.h"
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Parses a line containing a meta element (lightning, camera).
 */
int	parse_meta(char *line)
{
	(void)line;
	printf("[!] - Parsing a meta element...\n");
	return (0);
}

/**
 * @brief Parses a line containing a shape element (sphere, cylinder, plane...).
 */
int	parse_shape(char *line)
{
	(void)line;
	printf("[!] - Parsing a shape...\n");
	return (1);
}

/**
 * @brief Parses a given .rt file and creates the scene from it.
 *
 * @details Error messages:
 * 0 - All went well
 * 1 - Path is not a .rt file
 * 2 - Failed to open the file
 */
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
