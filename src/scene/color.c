#include "color.h"

#include <stdint.h>

/**
 * @brief Create a new `t_color` struct.
 * Warning: values are a range from 0 to 255.
 */
t_color	make_color(float r, float g, float b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
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

/**
 * @brief Restrict a color's values to a minimum of 0 and a maximum of 1.
 */
void	color_clamp(t_color *color)
{
	// TODO: make a `clamp(min, max)` function in some utils file and call it here for each value
	if (color->r < 0.0)
		color->r = 0.0;
	else if (color->r > 1.0)
		color->r = 1.0;
	if (color->g < 0.0)
		color->g = 0.0;
	else if (color->g > 1.0)
		color->g = 1.0;
	if (color->b < 0.0)
		color->b = 0.0;
	else if (color->b > 1.0)
		color->b = 1.0;
}
