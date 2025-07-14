#ifndef HIERARCHY_H
# define HIERARCHY_H

# include "minirt.h"

typedef struct s_core t_core;
typedef struct s_shape t_shape;
typedef struct s_img t_img;

typedef struct s_rectangle
{
    int         height;
    int         width;
    int         color;
}   t_rectangle;

typedef struct s_edit_win
{
	t_core		*core;
	t_shape		*shape;
	void		*win;
	t_img		img;
}	t_edit_win;

// UI related functions - hierarchy.c / hierarchy_utils.c
void		render_shape_list(t_core *core);
void    	handle_page_click(int x);
void    	draw_edit_text(t_core *core, t_shape *shape, int y_offset);
void		open_edit_window(t_core *core, t_shape *shape);
int			shape_lst_size(t_shape *lst);
void		draw_rect(t_img *img, int x, int y, t_rectangle rec);
int			on_mouse_debug(int button, int x, int y, void *param);
t_rectangle new_rectangle(int width, int height, int color);

#endif