#ifndef MINIRT_H
# define MINIRT_H

// Macros //
# define WIN_WIDTH 1080
# define WIN_HEIGHT 1080

// Includes //
# include "scene.h"
# include "utils.h"

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

//	Holds render related variables
typedef struct s_render
{
	int	x;
	int	y;
	int	is_rendering;
}	t_render;

// Holds all MLX-related data
typedef struct s_core
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_scene	scene;
	int		render_mode;
	t_render render;
}	t_core;

// Result if a ray intersects with a (for now) sphere and its closest t on that
// ray
typedef struct s_result
{
	t_sphere	*closest;		// Closest object found
	double		closest_t;		// Closest t value for that object
}	t_result;

// Functions //

// General functions - minirt.c
t_core		*get_core(void);
int			rt_kill(t_core *core, int exit_code);

// MiniLibX helper functions - mlx.c
int			init_window(void);
void		img_put_pixel(t_img *img, int x, int y, t_color *color);

// Rendering functions - render.c
int			render(t_core *core, t_camera *camera);
int			render_loop(void *param);
int			fast_render_loop(void *param);
t_result	closest_intersect(t_point3 *origin, t_vec3 *dir, t_range t_range);

#endif //MINIRT_H
