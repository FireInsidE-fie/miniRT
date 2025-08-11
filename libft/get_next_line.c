/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estettle <estettle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:01:24 by estettle          #+#    #+#             */
/*   Updated: 2024/10/23 15:02:44 by estettle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* read_buffer()
 * invokes read() on the file descriptor given in the fd argument and stores the
 * result in the stash variable.
 * returns the number of bytes read.
*/
static int	read_buffer(char **stash, int fd)
{
	int		read_count;
	char	*buffer;
	char	*tmp;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	read_count = read(fd, buffer, BUFFER_SIZE);
	buffer[read_count] = 0;
	tmp = ft_strjoin(*stash, buffer);
	free(buffer);
	free(*stash);
	if (!tmp)
	{
		*stash = NULL;
		return (-1);
	}
	*stash = tmp;
	return (read_count);
}

/* parse_line()
 * checks the stash for a new line character. if one is found, return the
 * corresponding line, if not, it invokes read_buffer() to read from the fd
 * until stash contains a new line character or the end of the file descriptor's
 * content is reached (read_count == 0).
 * returns the line found, either to a \n character or to the end of the fd.
*/
static char	*parse_line(char **stash, int fd)
{
	int		read_count;

	if (ft_strchr(*stash, '\n'))
		return (ft_substr(*stash, 0, ft_strchr(*stash, '\n') - *stash + 1));
	read_count = 1;
	while (read_count > 0)
	{
		read_count = read_buffer(stash, fd);
		if (read_count <= 0)
		{
			if (read_count == 0 && ft_strlen(*stash) > 0)
				return (ft_strjoin("", *stash));
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		if (ft_strchr(*stash, '\n'))
			return (ft_substr(*stash, 0, ft_strchr(*stash, '\n') - *stash + 1));
	}
	return (ft_substr(*stash, 0, ft_strlen(*stash)));
}

/* catchup_stash()
 * this function creates a copy of the stash variable trimmed of the first
 * \n terminated string that's inside, and replaces the original stash with the
 * copy.
 * returns 0 on success, -1 on mem alloc failure.
*/
static int	catchup_stash(char **stash)
{
	char	*nl_index;
	char	*tmp;

	nl_index = ft_strchr(*stash, '\n');
	if (nl_index)
	{
		tmp = ft_substr(*stash, nl_index - *stash + 1,
				ft_strlen(*stash) - (nl_index - *stash));
		if (!tmp)
		{
			free(*stash);
			*stash = NULL;
			return (-1);
		}
	}
	else
		tmp = NULL;
	free(*stash);
	*stash = tmp;
	return (0);
}

/* get_next_line()
 * this function reads from the <fd> file descriptor and returns the first line
 * it founds. a line is a string terminated by either a new line character or
 * the end of the file descriptor's contents. see above functions for each step
 * of the execution.
 * returns a malloced string containing the line it found, or NULL if an error
 * occured somewhere (most likely malloc error).
*/
char	*get_next_line(int fd)
{
	char		*line;
	static char	*stashes[256];
	char		**stash;

	stash = &stashes[fd];
	if (fd < 0 || fd > 256 || read(fd, 0, 0) < 0 || BUFFER_SIZE == 0)
	{
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	if (!*stash)
		*stash = ft_calloc(sizeof(char), 1);
	if (!*stash)
		return (NULL);
	line = parse_line(stash, fd);
	if (!line || catchup_stash(stash) == -1)
	{
		free(line);
		free(*stash);
		*stash = NULL;
		return (NULL);
	}
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

// don't forget to always include a single (or two!) file path, silly
int	main(int argc, char **argv)
{
	int		fd1;
	int		fd2;
	//char	*str;

	if (argc != 3)
		return (0);

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);

	printf("[!] - Reading two lines...\n");
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));

	close(fd1);

	//fd2 = open(argv[1], O_RDONLY);

	//printf("\n\n[!] - Reading entire file...\n");
	//str = get_next_line(fd2);
	//while (str)
	//{
	//	printf("%s", str);
	//	str = get_next_line(fd2);
	//}

	//free(str);

	//close(fd2);

}
*/
