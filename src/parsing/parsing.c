#include "get_next_line.h"
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

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
	char	*line;

	assert(scene_path && "Scene Path");
	scene_fd = open(scene_path, O_RDONLY);
	if (scene_fd == -1)
		return (perror("miniRT - parse_scene (open)"), 2);
	line = get_next_line(scene_fd);
	while (line)
	{
		write(1, line, ft_strlen(line));
		line = get_next_line(scene_fd);
	}
	return (0);
}
