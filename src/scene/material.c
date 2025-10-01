#include "material.h"
#include "utils.h"

#include <stdio.h>
#include <stdint.h>

/**
 * @brief Multiplies a color by a given factor.
 */
t_color	color_mult(t_color c, float factor)
{
	t_range	range;
	t_color	result;

	range = (t_range){0.0, 1.0};
	result.r = clamp(c.r * factor, range);
	result.g = clamp(c.g * factor, range);
	result.b = clamp(c.b * factor, range);
	return (result);
}

t_color	color_add(t_color a, t_color b)
{
	t_range	range;
	t_color	result;

	range = (t_range){0.0, 1.0};
	result.r = clamp(a.r + b.r, range);
	result.g = clamp(a.g + b.g, range);
	result.b = clamp(a.b + b.b, range);
	return (result);
}

/**
 * @brief Converts a `t_color` struct's value into an 8-byte representation
 * following the template 0xAARRGGBB.
 *
 * @details
 * a for transparency.
 * r for red value.
 * g for green value.
 * b for blue value.
 */
uint32_t	color_to_int(t_color *color)
{
	uint32_t	rgba;

	rgba = 0;
	rgba |= (uint32_t)(color->r * 255) << 16;
	rgba |= (uint32_t)(color->g * 255) << 8;
	rgba |= (uint32_t)(color->b * 255);
	return (rgba);
}

void	print_mat(t_material *mat)
{
	printf("Color: (%f, %f, %f)\n", mat->color.r, mat->color.g, mat->color.b);
	printf("Specular: %f\n", mat->specular);
	printf("Reflection: %f\n", mat->reflection);
	printf("Texture: %d\n", mat->texture);
}
