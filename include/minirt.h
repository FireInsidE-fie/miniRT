#ifndef MINIRT_H
# define MINIRT_H

// Macros //
# define WIN_WIDTH 1080
# define WIN_HEIGHT 1080

// Includes //
# include "scene.h"

// Structs //

// A MLX image
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;		// Bits per pixel
	int		line_len;	// Bytes per line
	int		endian;		// Endianness
}	t_img;

// Holds all MLX-related data
typedef struct s_core
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_scene	*scene;
}	t_core;

// Functions //

// General functions - minirt.c
int		rt_kill(t_core *core, int exit_code);

// MiniLibX helper functions - mlx.c
t_core	*get_core(void);
int		init_window(void);
void	img_put_pixel(t_img *img, int x, int y, t_color *color);

// Rendering functions - render.c
int		render(t_core *core, t_camera *camera);

#endif //MINIRT_H
