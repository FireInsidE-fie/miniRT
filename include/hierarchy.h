#ifndef HIERARCHY_H
# define HIERARCHY_H

# include "minirt.h"

#define UI_BG_COLOR		0x343434
#define UI_DARK_GRAY	0x555555
#define UI_SHAPE_HEIGHT	50
#define MAX_PER_PAGE	12			// Max shapes per hierarchy page

typedef struct s_core t_core;
typedef struct s_shape t_shape;
typedef struct s_img t_img;

typedef struct s_rectangle
{
	int			height;
	int			width;
	int			color;
}   t_rectangle;

// Represents the edit window
typedef struct s_ewin
{
	t_core		*core;
	t_shape		*shape;
	void		*win;
	t_img		img;
}	t_ewin;

// UI related functions - hierarchy.c / hierarchy_utils.c
void		render_shape_list(t_core *core);
void		handle_page_click(int x);
void		draw_edit_text(t_core *core, t_shape *shape, int y_offset);
void		open_edit_window(t_core *core, t_shape *shape);
int			shape_lst_size(t_shape *lst);
void		draw_rect(t_img *img, int x, int y, t_rectangle rec);
int			on_mouse_debug(int button, int x, int y, void *param);
t_rectangle new_rectangle(int width, int height, int color);
int			close_edit_window(t_ewin *editwin);

// Sphere editing
int			on_mouse_edit_s(int button, int x, int y, void *param);
void		draw_edit_win_rec_s(t_ewin *editwin);
void   		edit_win_sphere(t_ewin *editwin);

// Plane editing
void	   	edit_win_plane(t_ewin *editwin);
void		draw_edit_win_rec_p(t_ewin *editwin);
int			on_mouse_edit_p(int button, int x, int y, void *param);

// Cylinder editing
void    	edit_win_cylinder(t_ewin *editwin);
void		draw_edit_win_rec_c(t_ewin *editwin);
int			on_mouse_edit_c(int button, int x, int y, void *param);


#endif
