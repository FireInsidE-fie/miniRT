#include "scene.h"
#include "ambient.h"
#include "material.h"

#include <stdio.h>

void	create_ambient(float intensity, t_color *color)
{
	t_ambient	*ambient;

	ambient = &get_scene()->ambient;
	ambient->intensity = intensity;
	ambient->color = *color;
}

void	print_ambient(t_ambient *ambient)
{
	printf(
		"[!] - Ambient\n"
		"Intensity: %f\n"
		"Color: (%f, %f, %f)\n",
		ambient->intensity,
		ambient->color.r, ambient->color.g, ambient->color.b
		);
}
