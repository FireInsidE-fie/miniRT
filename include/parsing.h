#ifndef PARSING_H
# define PARSING_H

# define SHAPE_ABBR_LENGTH 2	// Length of shape abbreviations in .rt files
# define META_ABBR_LENGTH 1		// Length of meta abbreviations in .rt files
# define TEXT_ABRR_LENGTH 2		// Length of texture abbreviations in .rt files

# include "material.h"
# include "point3.h"

typedef enum e_parsing_status
{
	DONE,			// All went well
	FILE_ERR,		// Path is not a .rt file
	OPEN_ERR,		// Failed to open the file
	TYPE_ERR,		// Abbreviation at start of line is wrong
	TRIAD_ERR,		// An error occurred while parsing a triad of numbers.
	CHAR_ERR,		// Line contained an invalid / erroneously placed character.
	MISSING_ERR,	// A value was missing from the line given the element type
	VALUE_ERR,		// A value was incorrect (negative colors for example)
	MALLOC_ERR,		// Allocation failed when creating an object
}	t_parsing_status;

// Main parsing functions - parsing.c
int		print_ps(t_parsing_status status, int line_n);
int		parse_scene(int scene_fd);

// Parsing meta elements - parsing_metas.c
int		parse_ambient(char *line);
int		parse_camera(char *line);
int		parse_light(char *line);

// Parsing shape elements - parsing_shapes.c
int		parse_sphere(char *line);
int		parse_cylinder(char *line);
int		parse_cone(char *line);
int		parse_plane(char *line);

// Parsing utilities - parsing_utils.c
int		parse_triad(char *str, float *result);
int		parse_position(char *line, t_point3 *result);
int		parse_material(char *line, t_material *mat);
int		goto_next_word(char **line);

#endif // PARSING_H
