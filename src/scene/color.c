#include "color.h"

#include <stdint.h>
#include <assert.h>

/**
 * @brief Create a new `t_color` struct.
 * Warning: values are a range from 0 to 255.
 */
t_color	make_color(float r, float g, float b)
{
	t_color	color;

	assert("Red Color" && r >= 0.0f && r <= 1.0f);
	assert("Green Color" && g >= 0.0f && g <= 1.0f);
	assert("Blue Color" && b >= 0.0f && b <= 1.0f);
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
