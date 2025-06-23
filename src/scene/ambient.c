#include "ambient.h"
#include "color.h"
#include "scene.h"

#include <assert.h>
#include <stdio.h>

void	create_ambient(float intensity, t_color color)
{
	t_ambient	*ambient;

	assert("Ambient light intensity" && intensity >= 0.0 && intensity <= 1.0);
	if (intensity < 0.0 || intensity > 1.0)
		printf("[!] - Ambient lightning sent with erroneous intensity (%f)\n",
			intensity);
	ambient = &get_scene()->ambient;
	ambient->intensity = intensity;
	ambient->color = color;
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
