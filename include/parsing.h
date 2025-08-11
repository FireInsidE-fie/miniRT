#ifndef PARSING_H
# define PARSING_H

# define SHAPE_ABBR_LENGTH 2	// Length of shape abbreviations in .rt files
# define META_ABBR_LENGTH 1		// Length of meta abbreviations in .rt files

typedef enum e_parsing_status {
	DONE,			// All went well
	PATH_ERR,		// Path is not a .rt file
	OPEN_ERR,		// Failed to open the file
	TYPE_ERR,		// Abbreviation at start of line is wrong
	TRIAD_ERR,		// An error occurred while parsing a triad of numbers.
	CHAR_ERR,		// Line contained an invalid character.
	MISSING_ERR,	// A value was missing from the line given the element type
	VALUE_ERR,		// A value was incorrect (negative colors for example)
}	t_parsing_status;

// Main parsing functions - parsing.c
int		parse_scene(char *scene_path);

// Parsing meta elements - parsing_metas.c
int		parse_ambient(char *line);
int		parse_camera(char *line);
int		parse_light(char *line);

// Parsing shape elements - parsing_shapes.c
int		parse_sphere(char *line);
int		parse_cylinder(char *line);
int		parse_plane(char *line);

// Parsing utilities - parsing_utils.c
float	ft_atof(char *str);
int		parse_triad(char *str, float *result);

#endif // PARSING_H
