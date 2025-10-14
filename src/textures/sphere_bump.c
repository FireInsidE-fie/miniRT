/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:25:55 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:26:37 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "textures.h"
#include "scene.h"
#include "vector.h"
#include "minirt.h"
#include "mlx.h"

#include <math.h>
#include <stdio.h>

/*
 * @brief Loading Bumpmap textures (.xpm)
 *
 * @details
 * We use a static void *img and static t_texturedata to avoid reloading the
 * xpm file or its data on every ray sent.
 * If the img doesn't exist yet, load it. If it exists
 * return the previously loaded t_texturedata texture.
 * Supports two flags: LOAD (0) or FREE (1). These will load and free
 * the textures respectively.
*/
t_texturedata	*load_earth_bumpmap(int flag)
{
	static void				*img;
	static t_texturedata	texture;

	if (!img && flag == LOAD)
	{
		img = mlx_xpm_file_to_image(get_core()->mlx,
				"src/textures/EARTH_BUMP.xpm",
				&texture.width, &texture.height);
		if (!img)
			return (NULL);
		texture.data = mlx_get_data_addr(img,
				&texture.bpp, &texture.line_len, &texture.endian);
	}
	if (img && flag != LOAD)
	{
		mlx_destroy_image(get_core()->mlx, img);
		return (NULL);
	}
	return (&texture);
}

/**
 * @see load_earth_bumpmap(int flag)
 */
t_texturedata	*load_moon_bumpmap(int flag)
{
	static void				*img;
	static t_texturedata	texture;

	if (!img && flag == LOAD)
	{
		img = mlx_xpm_file_to_image(get_core()->mlx,
				"src/textures/MOON_BUMP.xpm",
				&texture.width, &texture.height);
		if (!img)
			return (NULL);
		texture.data = mlx_get_data_addr(img,
				&texture.bpp, &texture.line_len, &texture.endian);
	}
	if (img && flag != LOAD)
	{
		mlx_destroy_image(get_core()->mlx, img);
		return (NULL);
	}
	return (&texture);
}

/**
 * @brief Returns the amount of gray a pixel has
 * (considering pixel[0] = pixel[1] = pixel[2])
 * @details Wraps around when x and/or y coordinates go futher than the texture
 * size.
 */
static float	get_grayscale(t_texturedata *tex, int x, int y)
{
	unsigned char	*pixel;
	int				offset;

	x = (x + tex->width) % tex->width;
	y = (y + tex->height) % tex->height;
	offset = y * tex->line_len + x * (tex->bpp / 8);
	pixel = (unsigned char *)(tex->data + offset);
	return (pixel[0] / 255.0f);
}

/*
 * @brief Returns a pertubed normal after applying bump.
 *
 * @details
 * We first retrieve the uv coords from the sphere.
 * The uv coords are then used to retrieve the wanted
 * pixel on the bumpmap texture image.
 *
 * get_grayscale retrieves the amount of gray the pixel has.
 * the h_x and h_y variables are used to compare the adjacent
 * pixel's grayscales.
 *
 * dx and dy hold the height differences between the adjacent
 * pixels. a strength value is used to scale the effect. We'll
 * use predefined values for strength as it depends on how well
 * made the bump map textures are made.
 *
 * Once we have gathered the grayscales, height differences,
 * uv coords. We set and return the final perturbed normal with
 * the horizontally perturbed tangeant (bm.tangeant) and the
 * vertically perturbed tangeant (bm.bitangeant).
 */
static t_vec3	perturb_normal(t_shape *sphere, t_point3 *p,
		t_texturedata *bump, float strength)
{
	t_bumpmap	bm;

	bm.w = bump->width;
	bm.h_tex = bump->height;
	bm.uv = sphere_uv_mapping(sphere, p);
	bm.x = (int)(bm.uv.u * bm.w);
	bm.y = (int)(bm.uv.v * bm.h_tex);
	bm.h = get_grayscale(bump, bm.x, bm.y);
	bm.h_x = get_grayscale(bump, (bm.x + 1) % bm.w, bm.y);
	bm.h_y = get_grayscale(bump, bm.x, (bm.y + 1) % bm.h_tex);
	bm.dx = (bm.h_x - bm.h) * strength;
	bm.dy = (bm.h_y - bm.h) * strength;
	bm.normal = point3_sub(p, &sphere->position);
	vec_normalize(&bm.normal);
	bm.tangent = (t_vec3){-sin(bm.uv.u * 2 * M_PI), 0, cos(bm.uv.u * 2 * M_PI)};
	bm.bitangent = (t_vec3){-cos(bm.uv.u * 2 * M_PI) * sin(bm.uv.v * M_PI),
		cos(bm.uv.v * M_PI), -sin(bm.uv.u * 2 * M_PI) * sin(bm.uv.v * M_PI)};
	vec_normalize(&bm.tangent);
	vec_normalize(&bm.bitangent);
	bm.perturbed = vec_add(
			vec_add(vec_scale(bm.tangent, bm.dx),
				vec_scale(bm.bitangent, bm.dy)), vec_scale(bm.normal, 1.0f));
	vec_normalize(&bm.perturbed);
	return (bm.perturbed);
}

void	apply_bump(t_shape *sphere, t_point3 *p, t_vec3 *normal, t_texture type)
{
	t_texturedata	*bump;

	if (type == EARTH)
	{
		bump = load_earth_bumpmap(0);
		if (!bump || !bump->data)
			return ;
		*normal = perturb_normal(sphere, p, bump, 111122.5f);
	}
	else if (type == MOON)
	{
		bump = load_moon_bumpmap(0);
		if (!bump || !bump->data)
			return ;
		*normal = perturb_normal(sphere, p, bump, 2.5f);
	}
}
