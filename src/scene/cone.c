#include "parsing.h"
#include "scene.h"
#include "vector.h"
#include "minirt.h"
#include "cone.h"

#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static bool	is_inside_cone_height(t_point3 *origin, t_vec3 *dir,
		t_shape *cone, double t)
{
	t_point3	p;
	t_vec3		v;
	t_vec3		scaled;
	double		h;

	scaled = point3_scale(dir, t);
	p = point3_add(origin, &scaled);
	v = point3_sub(&p, &cone->position);
	h = dot_product(&v, &cone->direction);
	if (h < 0.0 || h > cone->height)
		return (false);
	return (true);
}

// TODO: Dupe, will move things around
static t_vec3	project_vec(t_vec3 *v, t_vec3 *axis)
{
	t_vec3	proj;
	double	dot;

	dot = dot_product(v, axis);
	proj = point3_scale(axis, dot);
	return (proj);
}

/**
 * @brief ...
 *
 * @details
 * `oc`: Origin to cone tip vector
 * `proj_d`: How much does dir follows along cone->direction,
 * 0 if completely perpendicular
 * `proj_oc`: How much does origin to cone's tip segment/vector follows
 * along cone->direction
 * `d_proj`: How much does dir follows along cone->direction,
 * 0 if completely parallel (other axis)
 * `oc_proj`: How much does origin to cone's tip segment/vector
 * follows along cone->direction (other axis)
 * Good to note the cone's position is actually the tip point,
 * if you think about non-closed cones shown in the subject, it makes sense.
 */
static void	compute_cone_coeffs(t_vec3 *origin, t_vec3 *dir,
		t_shape *cone, double coeffs[3])
{
	t_vec3	oc;
	t_vec3	proj_d;
	t_vec3	proj_oc;
	t_vec3	d_proj;
	t_vec3	oc_proj;

	oc = point3_sub(origin, &cone->position);
	proj_d = project_vec(dir, &cone->direction);
	d_proj = point3_sub(dir, &proj_d);
	proj_oc = project_vec(&oc, &cone->direction);
	oc_proj = point3_sub(&oc, &proj_oc);
	coeffs[0] = dot_product(&d_proj, &d_proj)
		- pow((cone->radius / cone->height), 2)
		* dot_product(&proj_d, &proj_d);
	coeffs[1] = 2 * (dot_product(&d_proj, &oc_proj)
			- pow((cone->radius / cone->height), 2)
			* dot_product(&proj_d, &proj_oc));
	coeffs[2] = dot_product(&oc_proj, &oc_proj)
		- pow((cone->radius / cone->height), 2)
		* dot_product(&proj_oc, &proj_oc);
}

/**
 * @brief Computes whether a ray starting at `origin` with direction `dir`
 * hits a `cone`, and stores the results in the `t` array of 2 doubles.
 */
bool	hit_cone(t_point3 *origin, t_vec3 *dir, t_shape *cone, double *t)
{
	double	coeffs[3];
	double	discriminant;
	double	sqrt_disc;
	double	a;
	double	b;

	compute_cone_coeffs(origin, dir, cone, coeffs);
	a = coeffs[0];
	b = coeffs[1];
	discriminant = (b * b) - (4 * a * coeffs[2]);
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrt(discriminant);
	t[0] = (-b - sqrt_disc) / (2 * a);
	t[1] = (-b + sqrt_disc) / (2 * a);
	if (!is_inside_cone_height(origin, dir, cone, t[0]))
		t[0] = INFINITY;
	if (!is_inside_cone_height(origin, dir, cone, t[1]))
		t[1] = INFINITY;
	if (t[0] == INFINITY && t[1] == INFINITY)
		return (false);
	return (true);
}

void	handle_cone_intersect(double t[2], t_shape *cone, t_result *result)
{
	if (t[0] >= 0 && t[0] < result->closest_t)
	{
		result->closest = cone;
		result->closest_t = t[0];
	}
	if (t[1] >= 0 && t[1] < result->closest_t)
	{
		result->closest = cone;
		result->closest_t = t[1];
	}
}

void	compute_cone_light(t_vec3 *normal, t_point3 *intersect,
	t_color *color, t_result *result)
{
	t_shape	*cone;

	cone = result->closest;
	*normal = get_cone_normal(cone, intersect);
	*color = cone->mat.color;
}

/**
 * @details
 * `base_to_p`: from cone->pos (tip) to intersect vector
 * `axis`: point reached within cone->direction from tip to dir scaled with m
 * `proj`: perpendicular with cone->dir, is placed where axis stops.
 * Has to get the proper incline applied on it in order to calculate the normal.
 * `m`: scalar used to determine how much base_to_p follows cone->direction
 */
t_vec3	get_cone_normal(t_shape *cone, t_point3 *intersect)
{
	t_vec3	base_to_p;
	t_vec3	axis;
	t_vec3	proj;
	t_vec3	normal;
	double	m;

	base_to_p = point3_sub(intersect, &cone->position);
	m = dot_product(&base_to_p, &cone->direction);
	axis = point3_scale(&cone->direction, m);
	proj = point3_sub(&base_to_p, &axis);
	proj = point3_scale(&proj, 1.0 / (pow((cone->radius / cone->height), 2)));
	normal = point3_add(&proj, &axis);
	vec_normalize(&normal);
	return (normal);
}

int	create_cone(t_shape *tmp)
{
	t_shape	*cone;

	assert("Radius" && tmp->radius > 0);
	assert("Height" && tmp->height > 0);
	assert("Material" && tmp->mat.color.r >= 0.0f && tmp->mat.color.r <= 1.0f
		&& tmp->mat.color.g >= 0.0f && tmp->mat.color.g <= 1.0f
		&& tmp->mat.color.b >= 0.0f && tmp->mat.color.b <= 1.0f);
	cone = malloc(sizeof(t_shape));
	if (!cone)
		return (perror("miniRT: create_cone - malloc"), MALLOC_ERR);
	cone->type = CONE;
	cone->position = tmp->position;
	vec_normalize(&tmp->direction);
	cone->direction = tmp->direction;
	cone->radius = tmp->radius;
	cone->height = tmp->height;
	cone->mat = tmp->mat;
	cone->next = NULL;
	add_shape(cone);
	return (DONE);
}

void	print_cone(t_shape *cone)
{
	assert("Cone" && cone);
	assert("Shape type" && cone->type == CONE);
	printf(
		"[!] - Cone\n"
		"Position: (%f, %f, %f)\n"
		"Direction: (%f, %f, %f)\n"
		"Radius: %f\n"
		"Height: %f\n",
		cone->position.x, cone->position.y, cone->position.z,
		cone->direction.x, cone->direction.y, cone->direction.z,
		cone->radius, cone->height
		);
	print_mat(&cone->mat);
}
