#include "scene.h"
#include "cylinder.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>

/**
 *	The initial intersect calculation for a cylinder will end up with an
	infinitely long cylinder. We check with this function if we are
	inside the wanted "final" cylinder.

	point	p = origin + dir * t
	vector	v = p - cyl->position
	height	h = dot(v, direction)

	the shape's base is cyl->position. direction is the shape's central axis.
	
	with the "base position", we can make an infinite cylinder growing
	towards "direction". with h, we can decide to only grow a certain height.
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
/**
 * @brief Projects supposedly normalized vector "v" on a "u" axis
 */
static t_vec3	project_vec(t_vec3 *v, t_vec3 *axis)
{
	t_vec3	proj;
	double	dot;

	dot = dot_product(v, axis);
	proj = point3_scale(axis, dot);
	return (proj);
}

/**
	Computes the coefficients of the quadratic equation for cylinders.
		(seatbelt on sweetie this one's harder)
	Coeffs 0 1 2 indicates a, b, c
 */
static void	compute_cylinder_coeffs(t_vec3 *origin, t_vec3 *dir,
					t_shape *cyl, double coeffs[3])
{
	t_vec3	oc;			// cylinder to origin ray
	t_vec3	proj_d;		// direction parallel to axis
	t_vec3	proj_oc;	// direction perpendicular to axis
	t_vec3	d_proj;		// origin parallel to axis
	t_vec3	oc_proj;	// oridin perpendicular to axis

	// Cylinder base to oriding ray
	oc = point3_sub(origin, &cyl->position);

	// Projection of the ray's direction on the cylinder's axis
	proj_d = project_vec(dir, &cyl->direction);
	d_proj = point3_sub(dir, &proj_d);

	// Projection of origin's vector on the axis
	proj_oc = project_vec(&oc, &cyl->direction);
	oc_proj = point3_sub(&oc, &proj_oc);

	// Coefficients for the quadratic operation
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

	assert("Origin" && origin);
	assert("Direction" && dir);
	assert("Cylinder" && cyl && cyl->type == CYLINDER);
	assert("t" && t);
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

void	create_cylinder(t_point3 pos, t_vec3 dir, float radius, float height, t_material mat)
{
	t_shape *cyl = malloc(sizeof(t_shape));

	cyl->type = CYLINDER;
	cyl->position = pos;
	vec_normalize(&dir);
	cyl->direction = dir;
	cyl->radius = radius;
	cyl->height = height;
	cyl->mat = mat;
	cyl->next = NULL;
	add_shape(cyl);
}