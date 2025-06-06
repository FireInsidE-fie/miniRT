#ifndef MINIRT_H
# define MINIRT_H

// Macros //
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

// Includes //
# include "ambient.h"
# include "camera.h"
# include "light.h"
# include "sphere.h"
# include "plane.h"
# include "cylinder.h"

// Structs //

typedef struct s_scene
{
	t_camera	camera;
	t_ambient	ambient;
	t_light		*lights;
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_scene;

// Holds all MLX-related data
typedef struct s_core
{
	void	*mlx;
	void	*win;
	t_scene	*scene;
}	t_core;

// A MLX image
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

// Functions //

// General functions - minirt.c
int		rt_kill(t_core *core);

// MiniLibX helper functions - mlx.c
t_core	*get_core(void);
int		init_window(void);

#endif //MINIRT_H
