#ifndef MINIRT_H
# define MINIRT_H

// Macros //
# define WIN_WIDTH 1080
# define WIN_HEIGHT 1080
# define BLOCK_SIZE 480

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

// Holds render related variables
typedef struct s_render
{
	int	x;
	int	y;
	int	is_rendering;
}	t_render;

// Holds all MLX-related data
typedef struct s_core
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_scene		scene;
	int			render_mode;
	t_render	render;
	void		*altwin;
	t_img		ui_img;
	int			ui_img_init;
	int			prevent_close;
	int			page_idx;
}	t_core;

// Result if a ray intersects with a (for now) sphere and its closest t on that
// ray
typedef struct s_result
{
	t_shape		*closest;		// Closest object found
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
t_result	closest_intersect(t_point3 *origin, t_vec3 *dir, t_range t_range);
t_color		ray_color(t_point3 origin, t_vec3 dir, t_range t_range, int depth);
int			render(void *param);
t_vec3		get_cylinder_normal(t_shape *cyl, t_point3 *intersect);

// Fast rendering functions - fast_render.c
int			fast_render(void *param);

// Reflections - reflections.c
t_color 	compute_reflection(t_point3 *origin, t_vec3 *dir, t_result *result, int depth);
t_color 	scale_color(t_color c, float factor);
t_color		add_color(t_color a, t_color b);

// UI related functions - hierarchy.c / hierarchy_utils.c
int			on_mouse_debug(int button, int x, int y, void *param);
void		render_shape_list(t_core *core);

#endif //MINIRT_H
