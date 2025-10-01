#include "material.h"
#include "minirt.h"
#include "mlx.h"
#include "libft.h"
#include <math.h>

void	export_scene(void);
void	write_export(float n, int fd);
void	export_shapes(t_shape *shape, int fd);
void	export_meta(t_scene *scene, t_light *lights, int fd);
void	write_triad(float x, float y, float z, int fd);
char	*ftoa(float n);
