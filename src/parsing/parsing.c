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
	char	c;

	assert(scene_path && "Scene Path");
	scene_fd = open(scene_path, O_RDONLY);
	if (scene_fd == -1)
		return (perror("miniRT - parse_scene (open)"), 2);
	while (read(scene_fd, &c, 1) > 0)
		write(1, &c, 1);
	return (0);
}
