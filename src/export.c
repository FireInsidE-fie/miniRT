#include "material.h"
#include "minirt.h"
#include "mlx.h"
#include "movement.h"
#include "libft.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

static char *get_ftoa(char *fractmp, int integer)
{
	char	*tmp;
	int		intlen;
	int		fraclen;
	char	*result;

	tmp = ft_itoa(integer);
	intlen = (int)ft_strlen(tmp);
	fraclen = (int)ft_strlen(fractmp);
	result = ft_calloc(sizeof(char), (ft_strlen(tmp) + fraclen + 2));
	ft_strlcpy(result, tmp, intlen + 1);
	result[intlen] = '.';
	ft_strlcat(result, fractmp, intlen + fraclen + 2);
	free(tmp);
	free(fractmp);
	return result;
}

static char *get_ftoa_line(float fracpart)
{
	char	*tmpfrac;
	char	*result;
	int		i;
	int		j;
	int		num;

	i = 6;
	j = 0;
	num = (int)(round(fracpart));
	tmpfrac = ft_itoa(num);
	result = ft_calloc(sizeof(char), 7);
	while (i > (int)ft_strlen(tmpfrac))
	{
		i--;
		result[j] = '0';
		j++;
	}
	ft_strlcat(result, tmpfrac, 7);
	free(tmpfrac);
	return result;
}

static char *ftoa(float n)
{
	float	intpart;
	float	fracpart;
	char	*result;
	int		tmp;
	int		integer;

	tmp = 6;
	fracpart = modff(n, &intpart);
	if (fracpart < 0)
		fracpart = -fracpart;
	while (tmp > 0)
	{
		fracpart *= 10;
		tmp--;
	}
	result = get_ftoa_line(fracpart);
	integer = (int)intpart;
	result = get_ftoa(result, integer);
	return result;
}

static void write_triad(float x, float y, float z, int fd)
{
	char *str;

    str = ftoa(x);
    ft_putstr_fd(str, fd);
    ft_putstr_fd(",", fd);
    free(str);
	str = ftoa(y);
	ft_putstr_fd(str, fd);
    ft_putstr_fd(",", fd);
    free(str);
	str = ftoa(z);
	ft_putstr_fd(str, fd);
    ft_putstr_fd(" ", fd);
    free(str);
}

static void write_export(float n, int fd)
{
    char *str;

    str = ftoa(n);
    ft_putstr_fd(str, fd);
    ft_putstr_fd(" ", fd);
    free(str);
}

static void export_cone(t_shape *shape, int fd)
{
	ft_putstr_fd("co ", fd);
    write_triad(shape->position.x, shape->position.y, shape->position.z, fd);
    write_triad(shape->direction.x, shape->direction.y, shape->direction.z, fd);
	write_export(shape->radius, fd);
	write_export(shape->height, fd);
    write_triad(shape->mat.color.r * 255, shape->mat.color.g * 255, shape->mat.color.b * 255, fd);
	write_export(shape->mat.specular, fd);
	write_export(shape->mat.reflection, fd);
    ft_putendl_fd("", fd);
}

static void export_cylinder(t_shape *shape, int fd)
{
	ft_putstr_fd("cy ", fd);
    write_triad(shape->position.x, shape->position.y, shape->position.z, fd);
    write_triad(shape->direction.x, shape->direction.y, shape->direction.z, fd);
	write_export(shape->radius, fd);
	write_export(shape->height, fd);
    write_triad(shape->mat.color.r * 255, shape->mat.color.g * 255, shape->mat.color.b * 255, fd);
	write_export(shape->mat.specular, fd);
	write_export(shape->mat.reflection, fd);
    ft_putendl_fd("", fd);
}

static void export_plane(t_shape *shape, int fd)
{
	ft_putstr_fd("pl ", fd);
    write_triad(shape->position.x, shape->position.y, shape->position.z, fd);
	write_triad(shape->normal.x, shape->normal.y, shape->normal.z, fd);
    write_triad(shape->mat.color.r * 255, shape->mat.color.g * 255, shape->mat.color.b * 255, fd);
	write_export(shape->mat.specular, fd);
	write_export(shape->mat.reflection, fd);
	if (shape->mat.texture == CHECKERBOARD)
		ft_putstr_fd("CH ", fd);
    ft_putendl_fd("", fd);
}

static void export_sphere(t_shape *shape, int fd)
{
	ft_putstr_fd("sp ", fd);
    write_triad(shape->position.x, shape->position.y, shape->position.z, fd);
    write_export(shape->radius, fd);
    write_triad(shape->mat.color.r * 255, shape->mat.color.g * 255, shape->mat.color.b * 255, fd);
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

static void export_shapes(t_shape *shape, int fd)
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

static void export_lights(t_light *lights, int fd)
{
    while (lights != NULL)
    {
        ft_putstr_fd("L ", fd);
    	write_triad(lights->position.x, lights->position.y, lights->position.z, fd);
        write_export(lights->intensity, fd);
        write_triad(lights->color.r * 255, lights->color.r * 255, lights->color.r * 255, fd);
        ft_putendl_fd("", fd);
        lights = lights->next;
    }
}

static void export_cam(t_scene *scene, int fd)
{
    ft_putstr_fd("C ", fd);
    write_triad(scene->camera.position.x, scene->camera.position.y, scene->camera.position.z, fd);
    write_triad(0.000000f, 0.000000f, 1.000000f, fd);
    write_export(scene->camera.fov, fd);
    ft_putendl_fd("", fd);
}

static void export_ambient(t_scene *scene, int fd)
{
    ft_putstr_fd("A ", fd);
    write_export(scene->ambient.intensity, fd);
    write_triad(scene->ambient.color.r * 255, scene->ambient.color.g * 255, scene->ambient.color.b * 255, fd);
    ft_putendl_fd("", fd);
}

void export_scene()
{
	int		fd;
	t_scene* scene;
	t_light* lights;
    t_shape* shape;
	
	scene = get_scene();
    lights = scene->lights;
	shape = scene->shapes;
	fd = open("exported.rt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	export_ambient(scene, fd);
	export_cam(scene, fd);
    ft_putendl_fd("", fd);
	export_lights(lights, fd);
	export_shapes(shape, fd);
}
