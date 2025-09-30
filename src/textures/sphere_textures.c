#include "sphere.h"
#include "textures.h"
#include "scene.h"
#include "vector.h"
#include "minirt.h"
#include "material.h"
#include "mlx.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

/*
 * @brief Returns an t_uv struct
 *
 * @details
 * uv stands for 2D coordinates, (x, y, z are already taken by t_point3 *point)
 * Basically, you turn your sphere into a 2d flat map. You then fetch the u,v
 * coords with your x, y, z hitpoint.
 * imagine having a world globe, putting a dart on Sydney.
 * t_uv would contain the 2d coords of Sydney on a 2d map of the earth.
*/
t_uv	sphere_uv_mapping(t_shape *sphere, t_point3 *point)
{
	t_vec3	local;
	t_uv	uv;

	local = point3_sub(point, &sphere->position);
	vec_normalize(&local);
	uv.u = 0.5 + atan2(local.z, local.x) / (2 * M_PI);
	uv.v = 0.5 - asin(local.y) / M_PI;
	return (uv);
}

/*
 * @brief Loading Map textures (.xpm)
 *
 * @details
 * We use a static void *img and static t_texturedata to avoid reloading the
 * xpm file or its data on every ray sent.
 * If the img doesn't exist yet, load it. If it exists
 * return the previously loaded t_texturedata texture.
 * Supports two flags: LOAD (0) or FREE (1). These will load and free
 * the textures respectively.
*/
t_texturedata	*load_moon_texture(int flag)
{
	static void				*img;
	static t_texturedata	texture;
	void					*mlx;

	if (!img)
	{
		mlx = get_core()->mlx;
		img = mlx_xpm_file_to_image(mlx, "src/textures/MOON.xpm",
				&texture.width, &texture.height);
		if (!img)
			return (NULL);
		texture.data = mlx_get_data_addr(img,
				&texture.bpp, &texture.line_len, &texture.endian);
	}
	if (img && flag != LOAD)
	{
		mlx_destroy_image(mlx, img);
		return (NULL);
	}
	return (&texture);
}

/**
 * @see load_earth_texture(int flag)
 */
t_texturedata	*load_earth_texture(int flag)
{
	static void				*img;
	static t_texturedata	texture;
	void					*mlx;

	mlx = get_core()->mlx;
	if (!img)
	{
		img = mlx_xpm_file_to_image(mlx, "src/textures/EARTH.xpm",
				&texture.width, &texture.height);
		if (!img)
			return (NULL);
		texture.data = mlx_get_data_addr(img,
				&texture.bpp, &texture.line_len, &texture.endian);
	}
	if (img && flag != LOAD)
	{
		mlx_destroy_image(mlx, img);
		return (NULL);
	}
	return (&texture);
}

/*
 * @brief Returns a t_color with t_uv coords in a t_texturedata
 *
 * @details
 * Fetches the colors at uv coords in an image.
 * Goes back in circle if going beyond the map.
*/
static t_color	get_texture_color(t_texturedata *tex, t_uv uv)
{
	int				x;
	int				y;
	unsigned char	*pixel;

	x = ((int)(uv.u * tex->width)) % tex->width;
	y = ((int)(uv.v * tex->height)) % tex->height;
	if (x < 0)
		x += tex->width;
	if (y < 0)
		y += tex->height;
	pixel = (unsigned char *)(tex->data
			+ y * tex->line_len + x * (tex->bpp / 8));
	return ((t_color){
		pixel[2] / 255.0f,
		pixel[1] / 255.0f,
		pixel[0] / 255.0f
	});
}

/*
 * @brief Calls the approriate functions depending on the needed texture.
 *
 * @details
 * If there was a texture needed, and it couldn't find it, it returns
 * a pink color.
*/
t_color	get_checker_color(t_shape *sphere, t_point3 *point)
{
	t_uv			uv;
	t_texturedata	*tex;

	if (sphere->mat.texture != EARTH && sphere->mat.texture != MOON
		&& sphere->mat.texture != CHECKERBOARD)
		return (sphere->mat.color);
	uv = sphere_uv_mapping(sphere, point);
	if (sphere->mat.texture == CHECKERBOARD)
		return (apply_checker_sphere(sphere, uv));
	if (sphere->mat.texture == EARTH)
		tex = load_earth_texture(LOAD);
	else
		tex = load_moon_texture(LOAD);
	if (!tex || !tex->data)
		return ((t_color){1, 0, 1});
	return (get_texture_color(tex, uv));
}
