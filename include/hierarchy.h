#ifndef HIERARCHY_H
# define HIERARCHY_H

# include "minirt.h"

# define UI_BG_COLOR		0x343434
# define UI_TEXT_COLOR		0xFFFFFF
# define UI_DARK_GRAY		0x555555
# define UI_SHAPE_HEIGHT	50
# define MAX_PER_PAGE		12			// Max shapes per hierarchy page

# define EWIN_RED	0xfc5656
# define EWIN_GREEN	0x56fc61
# define EWIN_B	30						// Edit window button size
# define EWIN_WIDTH	400
# define EWIN_HEIGHT	300

typedef struct s_core	t_core;
typedef struct s_shape	t_shape;
typedef struct s_img	t_img;

typedef struct s_rectangle
{
	int			height;
	int			width;
	int			color;
}	t_rectangle;

// Represents the edit window
typedef struct s_ewin
{
	t_core		*core;
	t_shape		*shape;
	void		*win;
	t_img		img;
	void		*color_picker_img;
	int			cp_x;
	int			cp_y;
	int			cp_w;
	int			cp_h;
}	t_ewin;

// UI related functions - hierarchy.c / hierarchy_utils.c
void		render_shape_list(t_core *core);
void		open_ewin(t_core *core, t_shape *shape);
int			on_mouse_debug(int button, int x, int y, void *param);
int			close_ewin(t_ewin *ewin);

// Hierarchy utils - hierarchy_utils.c
int			shape_lst_size(t_shape *lst);
void		draw_edit_text(t_core *core, t_shape *shape, int y_offset);
void		handle_page_click(int x);
t_rectangle	new_rec(int width, int height, int color);
void		draw_rect(t_img *img, int x, int y, t_rectangle rec);

// Sphere editing
int			on_mouse_edit_s(int button, int x, int y, void *param);
void		draw_ewin_rec_s(t_ewin *ewin);
void		ewin_sphere(t_ewin *ewin);

// Plane editing
void		ewin_plane(t_ewin *ewin);
void		draw_ewin_rec_p(t_ewin *ewin);
int			on_mouse_edit_p(int button, int x, int y, void *param);

// Cylinder editing
void		ewin_cylinder(t_ewin *ewin);
void		draw_ewin_rec_c(t_ewin *ewin);
int			on_mouse_edit_c(int button, int x, int y, void *param);

// color_picker.c
void		draw_color_picker(t_ewin *ewin, int x, int y);
void		fetch_color_from_picker(int mouse_x, int mouse_y, t_ewin *ewin);

#endif	// HIERARCHY_H
