#include "minirt.h"
#include "light.h"
#include "vector.h"
#include "material.h"

static t_color	get_light_exposure(
	t_origin origin, t_vec3 *normal, int specular, t_light *light)
{
	t_color	intensity;
	t_vec3	point_to_light;
	double	light_dot_normal;

	intensity = (t_color){0.0f, 0.0f, 0.0f};
	point_to_light = point3_sub(&light->position, origin.point);
	if (closest_intersect(origin, &point_to_light).closest)
	{
		light = light->next;
		return (intensity);
	}
	light_dot_normal = dot_product(&point_to_light, normal);
	if (light_dot_normal > 0)
		intensity = color_add(intensity, color_mult(
					light->color,
					light->intensity * light_dot_normal
					/ (vec_len(normal) * vec_len(&point_to_light))));
	if (specular != -1)
		intensity = color_add(
				intensity,
				color_mult(light->color,
					light->intensity * get_specular_reflection(
						origin.point, normal, &point_to_light, specular)));
	return (intensity);
}

/**
 * @brief Goes through all lights in the scene and computes a point's total
 * exposition to them, which is the addition of all lightning that hits it,
 * including ambient light.
 *
 * @details Of course, this often results in values over 1.0, or 100% of light.
 * Down the line, when this value is applied to the colors of an object, it will
 * be clamped down to 1.0 to ensure no color value goes over the maximum of 255.
 */
t_color	get_light_intensity(t_origin point, t_vec3 *normal, int specular)
{
	t_scene	*scene;
	t_color	intensity;
	t_light	*tmp;

	scene = get_scene();
	intensity = (t_color){
		scene->ambient.intensity * scene->ambient.color.r,
		scene->ambient.intensity * scene->ambient.color.g,
		scene->ambient.intensity * scene->ambient.color.b,
	};
	tmp = scene->lights;
	while (tmp)
	{
		intensity = color_add(
				intensity, get_light_exposure(point, normal, specular, tmp));
		tmp = tmp->next;
	}
	return (intensity);
}
