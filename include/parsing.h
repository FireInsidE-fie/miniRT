#ifndef PARSING_H
# define PARSING_H

# define SHAPE_ABBR_LENGTH 2	// Length of shape abbreviations in .rt files
# define META_ABBR_LENGTH 1		// Length of meta abbreviations in .rt files

// Main parsing functions - parsing.c
int	parse_scene(char *scene_path);

// Parsing meta elements - parsing_metas.c
int	parse_ambient(char *line);
int	parse_camera(char *line);
int	parse_light(char *line);

// Parsing shape elements - parsing_shapes.c
int	parse_sphere(char *line);
int	parse_cylinder(char *line);
int	parse_plane(char *line);

#endif // PARSING_H
