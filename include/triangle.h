#include "minirt.h"
#include "scene.h"
#include "point3.h"
#include "material.h"

#include <stdbool.h>

// Structure used to compute triangle intersection hits
// More details in triangle.c

typedef struct s_trhit
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	h;
	t_vec3	s;
	t_vec3	q;
	double	det;
	double	inv_det;
	double	u;
	double	v;
}	t_trhit;

bool	hit_triangle(t_point3 *orig, t_vec3 *dir, t_shape *tri, double *t);
void	handle_triangle_intersect(double t[2], t_shape *tri, t_result *result);
int		create_triangle(t_point3 a, t_point3 b, t_point3 c, t_material mat);
void	compute_triangle_light(t_vec3 *normal, t_color *color,
			t_result *result);
