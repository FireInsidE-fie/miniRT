/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:25:25 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:26:37 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "scene.h"
#include "cylinder.h"
#include "vector.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The initial intersect calculation for a cylinder will end up with an
 * infinitely long cylinder. We check with this function if we are
 * inside the wanted "final" cylinder.
 *
 * @details
 * point	p = origin + dir * t
 * vector	v = p - cyl->position
 * height	h = dot(v, direction)
 *
 * the shape's base is cyl->position. direction is the shape's central axis.

 * with the "base position", we can make an infinite cylinder growing
 * towards "direction". with h, we can decide to only grow a certain height.
 */
static bool	is_inside_cylinder_height(t_point3 *origin, t_vec3 *dir,
		t_shape *cyl, double t)
{
	t_point3	p;
	t_vec3		v;
	t_vec3		scaled;
	double		h;

	scaled = point3_scale(dir, t);
	p = point3_add(origin, &scaled);
	v = point3_sub(&p, &cyl->position);
	h = dot_product(&v, &cyl->direction);
	if (h < 0.0 || h > cyl->height)
		return (false);
	return (true);
}

/*
 * @brief Computes the coefficients of the quadratic equation for cylinders.
 * @details
 * Coeffs 0 1 2 indicates a, b, c
 * `oc`: cylinder to origin ray
 * `proj_d`: direction parallel to axis
 * `proj_oc`: direction perpendicular to axis
 * `d_proj`: origin parallel to axis
 * `oc_proj`: origin perpendicular to axis
 */
static void	compute_cylinder_coeffs(t_vec3 *origin, t_vec3 *dir,
					t_shape *cyl, double coeffs[3])
{
	t_vec3	oc;
	t_vec3	proj_d;
	t_vec3	proj_oc;
	t_vec3	d_proj;
	t_vec3	oc_proj;

	oc = point3_sub(origin, &cyl->position);
	proj_d = project_vec(dir, &cyl->direction);
	d_proj = point3_sub(dir, &proj_d);
	proj_oc = project_vec(&oc, &cyl->direction);
	oc_proj = point3_sub(&oc, &proj_oc);
	coeffs[0] = dot_product(&d_proj, &d_proj);
	coeffs[1] = 2 * dot_product(&d_proj, &oc_proj);
	coeffs[2] = dot_product(&oc_proj, &oc_proj) - cyl->radius * cyl->radius;
}

/**
 *	Find out if we are hitting a cylinder with our ray.
 */
bool	hit_cylinder(t_point3 *origin, t_vec3 *dir, t_shape *cyl, double *t)
{
	double	coeffs[3];
	double	discriminant;
	double	sqrt_disc;
	double	a;
	double	b;

	compute_cylinder_coeffs(origin, dir, cyl, coeffs);
	a = coeffs[0];
	b = coeffs[1];
	discriminant = (b * b) - (4 * a * coeffs[2]);
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrt(discriminant);
	t[0] = (-b - sqrt_disc) / (2 * a);
	t[1] = (-b + sqrt_disc) / (2 * a);
	if (!is_inside_cylinder_height(origin, dir, cyl, t[0]))
		t[0] = INFINITY;
	if (!is_inside_cylinder_height(origin, dir, cyl, t[1]))
		t[1] = INFINITY;
	if (t[0] == INFINITY && t[1] == INFINITY)
		return (false);
	return (true);
}

int	create_cylinder(t_shape *tmp)
{
	t_shape	*cyl;

	cyl = malloc(sizeof(t_shape));
	if (!cyl)
		return (perror("miniRT: create_cylinder - malloc"), MALLOC_ERR);
	cyl->type = CYLINDER;
	cyl->position = tmp->position;
	vec_normalize(&tmp->direction);
	cyl->direction = tmp->direction;
	cyl->radius = tmp->radius;
	cyl->height = tmp->height;
	cyl->mat = tmp->mat;
	cyl->next = NULL;
	add_shape(cyl);
	return (DONE);
}

void	print_cylinder(t_shape *cylinder)
{
	printf(
		"[!] - Cylinder\n"
		"Position: (%f, %f, %f)\n"
		"Direction: (%f, %f, %f)\n"
		"Radius: %f\n"
		"Height: %f\n",
		cylinder->position.x, cylinder->position.y, cylinder->position.z,
		cylinder->direction.x, cylinder->direction.y, cylinder->direction.z,
		cylinder->radius, cylinder->height
		);
	print_mat(&cylinder->mat);
}
