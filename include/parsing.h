#ifndef PARSING_H
# define PARSING_H

# define SHAPE_ABBR_LENGTH 2	// Length of shape abbreviations in .rt files
# define META_ABBR_LENGTH 1		// Length of meta abbreviations in .rt files
# define TEXT_ABRR_LENGTH 2		// Length of texture abbreviations in .rt files

# include "material.h"
# include "scene.h"
# include "point3.h"

typedef enum e_ps
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
}	t_ps;

// Main parsing functions - parsing.c
t_ps	print_ps(t_ps status, int line_n);
int		parse_scene(int scene_fd);

// Parsing meta elements - parsing_metas.c
t_ps	parse_ambient(char *line);
t_ps	parse_camera(char *line);
t_ps	parse_light(char *line);

// Parsing shape elements - parsing_shapes.c
t_ps	parse_sphere(char *line);
t_ps	parse_cylinder(char *line);
t_ps	parse_cone(char *line);
t_ps	parse_plane(char *line);
t_ps	parse_triangle(char *line);

// Parsing pos and dir - parsing_posdir.c
t_ps	parse_pos_dir(char **line, t_shape *tmp);

// Parsing utilities - parsing_utils.c
t_ps	parse_triad(char *str, float *result);
t_ps	parse_position(char *line, t_point3 *result);
t_ps	parse_material(char *line, t_material *mat);
t_ps	goto_next_word(char **line);

#endif // PARSING_H
