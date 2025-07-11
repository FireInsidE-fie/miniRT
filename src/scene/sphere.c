#include "sphere.h"
#include "scene.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

/**
 * @brief Adds a new sphere element to the miniRT scene.
 */
// TODO: when parsing is done, take structs by reference rather than by value
// (for context, we can't yet because the test scene gives `create_sphere`
// rvalues)
int	create_sphere(t_point3 position, float radius, t_color color)
{
	t_shape		*sphere;

	assert("Radius" && radius > 0);
	assert("Color" && color.r >= 0.0f && color.r <= 1.0f
		&& color.g >= 0.0f && color.g <= 1.0f
		&& color.b >= 0.0f && color.b <= 1.0f);
	sphere = malloc(sizeof(t_shape));
	if (!sphere)
		return (perror("miniRT (create_sphere) - malloc"), 1);
	sphere->type = SPHERE;
	sphere->specular = 300;
	sphere->reflection = 0.0;
	sphere->height = -1.0;
	sphere->position = position;
	sphere->radius = radius;
	sphere->color = color;
	sphere->next = NULL;
	add_shape(sphere);
	return (0);
}

void	print_sphere(t_shape *sphere)
{
	assert("Sphere" && sphere);
	assert("Sphere type" && sphere->type == SPHERE);
	printf(
		"[!] - Sphere\n"
		"Position: (%f, %f, %f)\n"
		"Radius: %f\n"
		"Color: (%f, %f, %f)\n",
		sphere->position.x, sphere->position.y, sphere->position.z,
		sphere->radius,
		sphere->color.r, sphere->color.g, sphere->color.b
		);
}

/**
 * @brief Store the result(s) of a quadratic equation inside of the
 * double[2] `t`.
 * @return `true` if an answer was found, false if there is no answer.
 */
static bool	solve_quadratic(double a, double b, double c, double *t)
{
	double		discriminant;

	assert("t" && t);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (false);
	t[0] = (-b + sqrt(discriminant)) / (2 * a);
	t[1] = (-b - sqrt(discriminant)) / (2 * a);
	return (true);
}

/**
 * @brief Checks if a ray starting at `origin` in direction `dir` hits a sphere
 * `sphere`.
 *
 * @arg t t is a pointer to an array of two doubles for storing the two
 * solutions of the quadratic equation used to check if a ray is hitting the
 * sphere.
 */
bool	hit_sphere(t_point3 *origin, t_vec3 *dir, t_shape *sphere, double *t)
{
	t_point3	co;
	double		a;
	double		b;
	double		c;

	assert("Origin" && origin);
	assert("Direction" && dir);
	assert("Sphere" && sphere);
	assert("Time" && t);
	co.x = (origin->x - sphere->position.x);
	co.y = (origin->y - sphere->position.y);
	co.z = (origin->z - sphere->position.z);
	a = dot_product(dir, dir);
	b = 2 * dot_product(&co, dir);
	c = dot_product(&co, &co) - (sphere->radius * sphere->radius);
	return (solve_quadratic(a, b, c, t));
}
