#include "export.h"
#include "libft.h"

static	void	export_cone(t_shape *shape, int fd)
{
	ft_putstr_fd("co ", fd);
	write_triad(shape->position.x, shape->position.y, shape->position.z, fd);
	write_triad(shape->direction.x, shape->direction.y, shape->direction.z, fd);
	write_export(shape->radius * 2, fd);
	write_export(shape->height, fd);
	write_triad(shape->mat.color.r * 255,
		shape->mat.color.g * 255,
		shape->mat.color.b * 255, fd);
	write_export(shape->mat.specular, fd);
	write_export(shape->mat.reflection, fd);
	ft_putendl_fd("", fd);
}

static	void	export_cylinder(t_shape *shape, int fd)
{
	ft_putstr_fd("cy ", fd);
	write_triad(shape->position.x, shape->position.y, shape->position.z, fd);
	write_triad(shape->direction.x, shape->direction.y, shape->direction.z, fd);
	write_export(shape->radius * 2, fd);
	write_export(shape->height, fd);
	write_triad(shape->mat.color.r * 255,
		shape->mat.color.g * 255,
		shape->mat.color.b * 255, fd);
	write_export(shape->mat.specular, fd);
	write_export(shape->mat.reflection, fd);
	ft_putendl_fd("", fd);
}

static	void	export_plane(t_shape *shape, int fd)
{
	ft_putstr_fd("pl ", fd);
	write_triad(shape->position.x, shape->position.y, shape->position.z, fd);
	write_triad(shape->normal.x, shape->normal.y, shape->normal.z, fd);
	write_triad(shape->mat.color.r * 255,
		shape->mat.color.g * 255,
		shape->mat.color.b * 255, fd);
	write_export(shape->mat.specular, fd);
	write_export(shape->mat.reflection, fd);
	if (shape->mat.texture == CHECKERBOARD)
		ft_putstr_fd("CH ", fd);
	ft_putendl_fd("", fd);
}

static	void	export_sphere(t_shape *shape, int fd)
{
	ft_putstr_fd("sp ", fd);
	write_triad(shape->position.x, shape->position.y, shape->position.z, fd);
	write_export(shape->radius * 2, fd);
	write_triad(shape->mat.color.r * 255,
		shape->mat.color.g * 255,
		shape->mat.color.b * 255, fd);
	write_export(shape->mat.specular, fd);
	write_export(shape->mat.reflection, fd);
	if (shape->mat.texture == EARTH)
		ft_putstr_fd("EA ", fd);
	if (shape->mat.texture == MOON)
		ft_putstr_fd("MO ", fd);
	if (shape->mat.texture == CHECKERBOARD)
		ft_putstr_fd("CH ", fd);
	ft_putendl_fd("", fd);
}

void	export_shapes(t_shape *shape, int fd)
{
	while (shape != NULL)
	{
		if (shape->type == SPHERE)
			export_sphere(shape, fd);
		else if (shape->type == PLANE)
			export_plane(shape, fd);
		else if (shape->type == CYLINDER)
			export_cylinder(shape, fd);
		else if (shape->type == CONE)
			export_cone(shape, fd);
		shape = shape->next;
	}
}
