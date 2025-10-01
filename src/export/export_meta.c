#include "export.h"

void	export_lights(t_light *lights, int fd)
{
	while (lights != NULL)
	{
		ft_putstr_fd("L ", fd);
		write_triad(lights->position.x,
			lights->position.y,
			lights->position.z, fd);
		write_export(lights->intensity, fd);
		write_triad(lights->color.r * 255,
			lights->color.r * 255,
			lights->color.r * 255, fd);
		ft_putendl_fd("", fd);
		lights = lights->next;
	}
}

void	export_cam(t_scene *scene, int fd)
{
	ft_putstr_fd("C ", fd);
	write_triad(scene->camera.position.x,
		scene->camera.position.y,
		scene->camera.position.z, fd);
	write_triad(0.000000f, 0.000000f, 1.000000f, fd);
	write_export(scene->camera.fov, fd);
	ft_putendl_fd("", fd);
}

void	export_ambient(t_scene *scene, int fd)
{
	ft_putstr_fd("A ", fd);
	write_export(scene->ambient.intensity, fd);
	write_triad(scene->ambient.color.r * 255,
		scene->ambient.color.g * 255,
		scene->ambient.color.b * 255, fd);
	ft_putendl_fd("", fd);
}

void	export_meta(t_scene *scene, t_light *lights, int fd)
{
	export_ambient(scene, fd);
	export_cam(scene, fd);
	ft_putendl_fd("", fd);
	export_lights(lights, fd);
}
