#include "ambient.h"
#include "color.h"
#include "scene.h"

void	create_ambient(double intensity, t_color color)
{
	t_ambient	*ambient;

	ambient = &get_scene()->ambient;
	ambient->intensity = intensity;
	ambient->color = color;
}
