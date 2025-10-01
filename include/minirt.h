#ifndef MINIRT_H
# define MINIRT_H

// Macros //
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define BLOCK_SIZE 480

// Includes //
# include "scene.h"
# include "point3.h"

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
	int			key_state[256];
}	t_core;

// Result if a ray intersects with a shape and its closest t on that ray
typedef struct s_result
{
	t_shape		*closest;		// Closest object found
	double		closest_t;		// Closest t value for that object
}	t_result;

// Represents a point and the associated shape that emits it (if there is one)
// Mainly used for reflections (since rays start on a shape's surface)
typedef struct s_origin
{
	t_point3	*point;
	t_shape		*shape;
}	t_origin;

// Functions //

// General functions - minirt.c
t_core		*get_core(void);
int			rt_kill(int exit_code);

// MiniLibX helper functions - mlx.c
int			init_window(void);

// Rendering functions - render.c
t_result	closest_intersect(t_origin origin, t_vec3 *dir);
t_color		ray_color(t_point3 origin, t_shape *self, t_vec3 dir, int depth);
int			render(void *param);

// Fast rendering functions - fast_render.c
int			fast_render(void *param);
void		update_camera(t_core *core);

// Reflections - reflections.c
t_color		compute_reflection(
				t_origin origin, t_vec3 *dir, t_result *result, int depth);
t_color		scale_color(t_color c, float factor);
t_color		add_color(t_color a, t_color b);

// UI related functions - hierarchy.c / hierarchy_utils.c
int			on_mouse_debug(int button, int x, int y, void *param);
void		render_shape_list(t_core *core);

#endif //MINIRT_H
