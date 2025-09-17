#ifndef TEXTURE_H
# define TEXTURE_H

# include "scene.h"
# include "vector.h"
# include "texturedata.h"

typedef struct s_uv {
	float u;
	float v;
}	t_uv;

typedef struct s_bumpmap
{
    t_vec3  normal;
    t_vec3  tangent;
    t_vec3  bitangent;
    t_vec3  perturbed;
    t_uv    uv;
    int     x;
    int     y;
    int     w;
    int     h_tex;
    float   h;
    float   h_x;
    float   h_y;
    float   dx;
    float   dy;
}   t_bumpmap;

t_texturedata	*load_earth_texture(int flag);
t_texturedata	*load_moon_texture(int flag);
t_color	apply_checker_sphere(t_shape *sphere, t_uv uv);
t_color	apply_checker_plane(t_shape *plane, t_point3 *point);

void	apply_bump_moon(t_shape *sphere, t_point3 *point, t_vec3 *normal);
void	apply_bump_earth(t_shape *sphere, t_point3 *point, t_vec3 *normal);
t_texturedata    *load_earth_bumpmap(int flag);
t_texturedata    *load_moon_bumpmap(int flag);

t_uv	sphere_uv_mapping(t_shape *sphere, t_point3 *point);

#endif
