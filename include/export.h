#ifndef EXPORT_H
# define EXPORT_H

# include "scene.h"

void	export_scene(void);
void	write_export(float n, int fd);
void	export_shapes(t_shape *shape, int fd);
void	export_meta(t_scene *scene, t_light *lights, int fd);
void	write_triad(float x, float y, float z, int fd);
char	*ftoa(float n);

#endif // EXPORT_H
