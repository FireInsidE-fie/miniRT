#ifndef MATERIAL_H
# define MATERIAL_H

# include <stdint.h>

# define SKY_COLOR 0.1

typedef struct s_uv {
	float u;
	float v;
}	t_uv;

typedef struct s_texturedata
{
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texturedata;

// Enum for representing which texture is being used
typedef enum e_texture
{
	NONE,
	CHECKERBOARD,
	EARTH,			// Only for spheres
	MOON,			// Only for spheres
}	t_texture;

// Struct for an RGB color representation
typedef struct s_color
{
	float	r;		// Value from 0 to 1
	float	g;		// Value from 0 to 1
	float	b;		// Value from 0 to 1
}	t_color;

// Struct to represent an shape's material
typedef struct s_material
{
	t_color			color;
	float			specular;
	float			reflection;
	t_texture		texture;
	t_texturedata	texturedata;
}	t_material;

// Functions //

t_color		make_color(float r, float g, float b);
uint32_t	color_to_int(t_color *color);
t_material	make_mat(t_color color, float specular, float reflection);
void		print_mat(t_material *mat);

#endif // MATERIAL_H
