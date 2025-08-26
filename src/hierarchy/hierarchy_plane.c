#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define	EWIN_RED	0xfc5656
#define EWIN_GREEN	0x56fc61
#define EWIN_BUTTON	30
#define EWIN_WIDTH	400
#define EWIN_HEIGHT	300

/* Mouse hook called in edit_win_plane when an edit window is opened.

	Checks for the area clicked, matches the colored
	red and green squares buttons.
*/

int	on_mouse_edit_p(int button, int x, int y, void *param)
{
	t_ewin	*editwin;

	editwin = (t_ewin *)param;
	fetch_color_from_picker(x, y, editwin);
	if (button != 1)
		return (0);
	if (x >= 50 && x <= 80 && y >= 40 && y <= 70)
		editwin->shape->position.y += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 40 && y <= 70)
		editwin->shape->position.y -= 0.1f;
	else if (x >= 300 && x <= 380 && y >= 250 && y <= 280)
		return (close_edit_window(editwin));
	return (0);
}

/*
	Draws colored rectangles for the Edit window for Plane editing
*/

void	draw_edit_win_rec_p(t_ewin *editwin)
{
	draw_rect(&editwin->img, 0, 0, new_rectangle(EWIN_WIDTH, EWIN_HEIGHT, UI_BG_COLOR));
	draw_rect(&editwin->img, 50, 40, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 40, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	draw_rect(&editwin->img, 300, 250, new_rectangle(80, 30, 0xCC3333));
}

void    edit_win_plane(t_ewin *editwin)
{
    t_core *core;

    core = get_core();
    draw_edit_win_rec_p(editwin);
	mlx_put_image_to_window(core->mlx, editwin->win, editwin->img.img, 0, 0);
	draw_color_picker(editwin, 250, 160);
	mlx_string_put(core->mlx, editwin->win, 320, 270, 0xFFFFFF, "Close");
	mlx_string_put(core->mlx, editwin->win, 130, 55, 0xFFFFFF, "Y Axis");
	mlx_mouse_hook(editwin->win, on_mouse_edit_p, editwin);
}
