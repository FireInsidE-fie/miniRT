#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"
#include "material.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define	EWIN_RED	0xfc5656
#define EWIN_GREEN	0x56fc61
#define EWIN_BUTTON	30
#define EWIN_WIDTH	400
#define EWIN_HEIGHT	300

/* Mouse hook called in open_edit_window when an edit window is opened.

	Checks for the area clicked, matches the colored
	red and green squares buttons.
*/

/* 
	Yes double pointer for char **data, i think the mlx wants "a pointer to", so even
	though it's already a pointer it will just invalid read if just sending char *data
	to another function..
*/
int fetch_color_picker_data(t_ewin *editwin, char **data, int mouse_x, int mouse_y)
{
    int bpp;
    int line_len;
    int endian;
    int px;
    int py;

    *data = mlx_get_data_addr(editwin->color_picker_img, &bpp, &line_len, &endian);
    px = mouse_x - editwin->cp_x;
    py = mouse_y - editwin->cp_y;
    return (py * line_len + px * (bpp / 8));
}

void fetch_color_from_picker(int mouse_x, int mouse_y, t_ewin *editwin)
{
    char    *data;
    int     offset;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
    data = NULL;
    offset = fetch_color_picker_data(editwin, &data, mouse_x, mouse_y);
    if (!editwin->color_picker_img)
        return ;
    if (mouse_x < editwin->cp_x || mouse_x >= editwin->cp_x + editwin->cp_w || mouse_y < editwin->cp_y || mouse_y >= editwin->cp_y + editwin->cp_h)
        return ;
    b = data[offset + 0];
    g = data[offset + 1];
    r = data[offset + 2];
    editwin->shape->mat.color = (t_color){r / 255.0f, g / 255.0f, b / 255.0f};
    return ;
}


void	draw_color_picker(t_ewin *editwin, int x, int y)
{
	t_core	*core;

	editwin->cp_x = x;
	editwin->cp_y = y;
	core = get_core();
	editwin->color_picker_img = mlx_xpm_file_to_image(core->mlx, "src/hierarchy/8_1_.xpm", &editwin->cp_w, &editwin->cp_h);
	if (!editwin->color_picker_img)
		printf("Failed to open Color picker image.\n");
	mlx_put_image_to_window(core->mlx, editwin->win, editwin->color_picker_img, editwin->cp_x, editwin->cp_y);
}

int	on_mouse_edit_s(int button, int x, int y, void *param)
{
	t_ewin	*editwin;

	editwin = (t_ewin *)param;
	fetch_color_from_picker(x, y, editwin);
	if (button != 1)
		return (0);
	if (x >= 50 && x <= 80 && y >= 40 && y <= 70)
		editwin->shape->position.z += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 40 && y <= 70)
		editwin->shape->position.z -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 90 && y <= 120)
		editwin->shape->position.y += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 90 && y <= 120)
		editwin->shape->position.y -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 140 && y <= 170)
		editwin->shape->position.x += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 140 && y <= 170)
		editwin->shape->position.x -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 190 && y <= 220)
		editwin->shape->radius += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 190 && y <= 220)
		editwin->shape->radius -= 0.1f;
	else if (x >= 300 && x <= 380 && y >= 250 && y <= 280)
		return (close_edit_window(editwin));
	return (0);
}

/*
	Draws colored rectangles for the Edit window for Sphere editing
*/

void	draw_edit_win_rec_s(t_ewin *editwin)
{
	draw_rect(&editwin->img, 0, 0, new_rectangle(EWIN_WIDTH, EWIN_HEIGHT, UI_BG_COLOR));
	draw_rect(&editwin->img, 50, 40, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 40, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	draw_rect(&editwin->img, 50, 90, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 90, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	draw_rect(&editwin->img, 50, 140, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 140, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	draw_rect(&editwin->img, 50, 190, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 190, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	draw_rect(&editwin->img, 300, 250, new_rectangle(80, 30, 0xCC3333));
}

void    edit_win_sphere(t_ewin *editwin)
{
    t_core *core;

    core = get_core();
    draw_edit_win_rec_s(editwin);
	mlx_put_image_to_window(core->mlx, editwin->win, editwin->img.img, 0, 0);
	draw_color_picker(editwin, 250, 160);
	mlx_string_put(core->mlx, editwin->win, 320, 270, 0xFFFFFF, "Close");
	mlx_string_put(core->mlx, editwin->win, 130, 155, 0xFFFFFF, "X Axis");
	mlx_string_put(core->mlx, editwin->win, 130, 105, 0xFFFFFF, "Y Axis");
	mlx_string_put(core->mlx, editwin->win, 130, 55, 0xFFFFFF, "Z Axis");
	mlx_string_put(core->mlx, editwin->win, 130, 205, 0xFFFFFF, "Size/Radius");
	mlx_mouse_hook(editwin->win, on_mouse_edit_s, editwin);
}
