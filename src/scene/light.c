#include "light.h"
#include "material.h"
#include "point3.h"
#include "scene.h"
#include "vector.h"
#include "minirt.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

void	clear_lights(void *first)
{
	t_light	*current;
	t_light	*next;

	if (!first)
		return ;
	current = first;
	while (current)
	{
		printf("[!] Freeing light %p\n", (void *)current);
		next = current->next;
		free(current);
		current = next;
	}
}

t_light	*create_light(t_point3 position, float intensity, t_color color)
{
	t_scene	*scene;
	t_light	*light;
	t_light	*tmp;

	assert("Light Intensity" && intensity >= 0.0f && intensity <= 1.0f);
	assert("Light Color"
		&& color.r >= 0.0f && color.r <= 1.0f
		&& color.g >= 0.0f && color.g <= 1.0f
		&& color.b >= 0.0f && color.b <= 1.0f);
	light = malloc(sizeof(t_light));
	if (!light)
		return (perror("miniRT (create_light) - malloc"), NULL);
	light->position = position;
	light->intensity = intensity;
	light->color = color;
	light->next = NULL;
	scene = get_scene();
	if (!scene->lights)
	{
		scene->lights = light;
		return (light);
	}
	tmp = scene->lights;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = light;
	return (light);
}

void	print_light(t_light *light)
{
	assert("Light" && light);
	printf(
		"[!] - Light\n"
		"Position: (%f, %f, %f)"
		"\nIntensity: %f\n"
		"Color: (%f, %f, %f)\n",
		light->position.x, light->position.y, light->position.z,
		light->intensity,
		light->color.r, light->color.g, light->color.b
		);
}

t_vec3	reflect_ray(t_vec3 *ray, t_vec3 *normal)
{
	t_vec3	reflected;

	reflected = point3_scale(normal, 2 * dot_product(normal, ray));
	reflected = point3_sub(&reflected, ray);
	return (reflected);
}

static float	get_specular_reflection(t_vec3 *point,
								t_vec3 *normal,
								t_vec3 *point_to_light,
								int specular)
{
	t_vec3	reflected;
	double	r_dot_v;
	t_vec3	view;

	view = point3_sub(&get_scene()->camera.position, point);
	reflected = reflect_ray(point_to_light, normal);
	r_dot_v = dot_product(&reflected, &view);
	if (r_dot_v > 0)
		return (
			pow(r_dot_v / (vec_len(&reflected) * vec_len(&view)), specular));
	return (0.0);
}

t_color	get_light_exposure(
	t_point3 *point, t_vec3 *normal, int specular, t_light *light)
{
	t_color	intensity;
	t_vec3	point_to_light;
	double	light_dot_normal;

	intensity = (t_color){0.0f, 0.0f, 0.0f};
	point_to_light = point3_sub(&light->position, point);
	if (closest_intersect(point, &point_to_light, new_range(0.001, 1))
		.closest)
	{
		light = light->next;
		return (intensity);
	}
	light_dot_normal = dot_product(&point_to_light, normal);
	if (light_dot_normal > 0)
		intensity = add_color(intensity, scale_color(
					light->color,
					light->intensity * light_dot_normal
					/ (vec_len(normal) * vec_len(&point_to_light))));
	if (specular != -1)
		intensity = add_color(
				intensity,
				scale_color(light->color,
					light->intensity * get_specular_reflection(
						point, normal, &point_to_light, specular)));
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
t_color	get_light_intensity(t_point3 *point, t_vec3 *normal, int specular)
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
		intensity = add_color(
				intensity, get_light_exposure(point, normal, specular, tmp));
		tmp = tmp->next;
	}
	return (intensity);
}
