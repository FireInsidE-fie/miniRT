#include "material.h"
#include "textures.h"
#include "scene.h"
#include "vector.h"
#include "minirt.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

t_texturedata    *load_earth_bumpmap(int flag)
{
    static void                *img;
    static t_texturedata    texture;
    void                    *mlx;

    if (!img)
    {
        mlx = get_core()->mlx;
        img = mlx_xpm_file_to_image(mlx, "src/textures/EARTH_BUMP.xpm",
                &texture.width, &texture.height);
        if (!img)
            return (NULL);
        texture.data = mlx_get_data_addr(img,
                &texture.bpp, &texture.line_len, &texture.endian);
    }
    if (img && flag > 0)
    {
        mlx_destroy_image(get_core()->mlx, img);
        return (NULL);
    }
    return (&texture);
}

t_texturedata    *load_moon_bumpmap(int flag)
{
    static void                *img;
    static t_texturedata    texture;
    void                    *mlx;

    if (!img)
    {
        mlx = get_core()->mlx;
        img = mlx_xpm_file_to_image(mlx, "src/textures/MOON_BUMP.xpm",
                &texture.width, &texture.height);
        if (!img)
            return (NULL);
        texture.data = mlx_get_data_addr(img,
                &texture.bpp, &texture.line_len, &texture.endian);
    }
    if (img && flag > 0)
    {
        mlx_destroy_image(get_core()->mlx, img);
        return (NULL);
    }
    return (&texture);
}

// Read grayscale value from bump texture
static float    get_grayscale(t_texturedata *tex, int x, int y)
{
    unsigned char    *pixel;
    int                offset;

    // Wrapping around, when going further than the texture
    // size, go back to its start
    x = (x + tex->width) % tex->width;
    y = (y + tex->height) % tex->height;

    offset = y * tex->line_len + x * (tex->bpp / 8);
    pixel = (unsigned char *)(tex->data + offset);

    return (pixel[0] / 255.0f);
}

static t_vec3 compute_bumped_normal_from_heightmap(t_shape *sphere, t_point3 *point,
    t_texturedata *bump, float strength)
{
    t_bumpmap bm;
    // declaring Bump.xpm textures sizes
    bm.w = bump->width;
    bm.h_tex = bump->height;

    // Get UV coordinates of the sphere hit point
    bm.uv = sphere_uv_mapping(sphere, point);

    // Converting UV coords to a wanted pixel on the texture.
    bm.x = (int)(bm.uv.u * bm.w);
    bm.y = (int)(bm.uv.v * bm.h_tex);

    // Get the current pixel's grayscale.
    bm.h     = get_grayscale(bump, bm.x, bm.y);
    // Get the Adjacent (x+1) grayscale.
    bm.h_x   = get_grayscale(bump, (bm.x + 1) % bm.w, bm.y);
    // Get the Adjacent (y+1) grayscale.
    bm.h_y   = get_grayscale(bump, bm.x, (bm.y + 1) % bm.h_tex);

    // Compute the "Height difference"
    bm.dx = (bm.h_x - bm.h) * strength;
    bm.dy = (bm.h_y - bm.h) * strength;

    // Setting the geometric normal before bumping/perturbing the normal.
    bm.normal = point3_sub(point, &sphere->position);
    vec_normalize(&bm.normal);

    // Building a Stable TBN landmark. TBN stands for Tangent, BiTangent, Normal
    // Tangent is the Tangential ?? direction on the surface's point.
    // BiTangent is another Tangent, perpendicular to Tangent T.

    // Bumping/Perturbing the horizontal direction of the surface with u.
    bm.tangent = (t_vec3){ -sin(bm.uv.u * 2 * M_PI), 0, cos(bm.uv.u * 2 * M_PI) };
    // Bumping/Perturbing the vertical direction of the surface with v.
    bm.bitangent = (t_vec3){ -cos(bm.uv.u * 2 * M_PI) * sin(bm.uv.v * M_PI),
        cos(bm.uv.v * M_PI), -sin(bm.uv.u * 2 * M_PI) * sin(bm.uv.v * M_PI) };
    vec_normalize(&bm.tangent);
    vec_normalize(&bm.bitangent);

    // Setting the final bumped/perturbed normal.
    // Combining Tangent, Bitangent, scaled with dx and dy, and the sphere's normal.
    bm.perturbed = vec_add(
        vec_add(vec_scalar(bm.tangent, bm.dx),
        vec_scalar(bm.bitangent, bm.dy)), vec_scalar(bm.normal, 1.0f));
    vec_normalize(&bm.perturbed);

    return bm.perturbed;
}


void apply_bump_earth(t_shape *sphere, t_point3 *point, t_vec3 *normal)
{
    t_texturedata *bump = load_earth_bumpmap(0);
    if (!bump || !bump->data)
        return ;
    *normal = compute_bumped_normal_from_heightmap(sphere, point, bump, 111122.5f);
}


void apply_bump_moon(t_shape *sphere, t_point3 *point, t_vec3 *normal)
{
    t_texturedata *bump = load_moon_bumpmap(0);
    if (!bump || !bump->data)
        return ;
    *normal = compute_bumped_normal_from_heightmap(sphere, point, bump, 2.5f);
}
