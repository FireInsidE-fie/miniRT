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

void	apply_cyl_rad(t_ewin *editwin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 190 && y <= 220)
		editwin->shape->radius += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 190 && y <= 220)
		editwin->shape->radius -= 0.1f;
}

void	apply_cyl_dir(t_ewin *editwin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 40 && y <= 70)
		editwin->shape->direction.z += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 40 && y <= 70)
		editwin->shape->direction.z -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 90 && y <= 120)
		editwin->shape->direction.y += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 90 && y <= 120)
		editwin->shape->direction.y -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 140 && y <= 170)
		editwin->shape->direction.x += 0.1f;
}

void	apply_cyl_height(t_ewin *editwin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 240 && y <= 270)
		editwin->shape->height += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 240 && y <= 270)
		editwin->shape->height -= 0.1f;
}

void	apply_cyl_pos(t_ewin *editwin, int x, int y)
{
    if (x >= 250 && x <= 280 && y >= 40 && y <= 70)
		editwin->shape->position.z += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 40 && y <= 70)
		editwin->shape->position.z -= 0.1f;
	else if (x >= 250 && x <= 280 && y >= 90 && y <= 120)
		editwin->shape->position.y += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 90 && y <= 120)
		editwin->shape->position.y -= 0.1f;
	else if (x >= 250 && x <= 280 && y >= 140 && y <= 170)
		editwin->shape->position.x += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 140 && y <= 170)
		editwin->shape->position.x -= 0.1f;
}

int	on_mouse_edit_c(int button, int x, int y, void *param)
{
	t_ewin	*editwin;

	editwin = (t_ewin *)param;
	fetch_color_from_picker(x, y, editwin);
	if (button != 1)
		return (0);
	apply_cyl_pos(editwin, x, y);
	apply_cyl_rad(editwin, x, y);
	apply_cyl_dir(editwin, x, y);
	apply_cyl_height(editwin, x, y);
	if (x >= 300 && x <= 380 && y >= 250 && y <= 280)
		return (close_edit_window(editwin));
	return (0);
}

void	draw_edit_win_rec_c(t_ewin *editwin)
{
	draw_rect(&editwin->img, 0, 0, new_rectangle(EWIN_WIDTH, EWIN_HEIGHT, UI_BG_COLOR));

    // Dir Z
	draw_rect(&editwin->img, 50, 40,  new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 40,  new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	// Dir Y
	draw_rect(&editwin->img, 50, 90,  new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 90,  new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	// Dir X
	draw_rect(&editwin->img, 50, 140, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 140, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
    // Pos Z
    draw_rect(&editwin->img, 250, 40,  new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 290,  40,  new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	// Pos Y
	draw_rect(&editwin->img, 250, 90,  new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 290,  90,  new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	// Pos X
	draw_rect(&editwin->img, 250, 140, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 290,  140, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	// Radius/Size
	draw_rect(&editwin->img, 50, 190, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 190, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
	// Height
	draw_rect(&editwin->img, 50, 240, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_GREEN));
	draw_rect(&editwin->img, 90, 240, new_rectangle(EWIN_BUTTON, EWIN_BUTTON, EWIN_RED));
    // Close
	draw_rect(&editwin->img, 300, 250, new_rectangle(80, 30, 0xCC3333));
}

void    edit_win_cylinder(t_ewin *editwin)
{
    t_core *core = get_core();

    draw_edit_win_rec_c(editwin);
	mlx_put_image_to_window(core->mlx, editwin->win, editwin->img.img, 0, 0);
	draw_color_picker(editwin, 250, 180);
	mlx_string_put(core->mlx, editwin->win, 320, 270, 0xFFFFFF, "Close");
	mlx_string_put(core->mlx, editwin->win, 130, 55, 0xFFFFFF, "Dir Z");
	mlx_string_put(core->mlx, editwin->win, 130, 105, 0xFFFFFF, "Dir Y");
	mlx_string_put(core->mlx, editwin->win, 130, 155, 0xFFFFFF, "Dir X");
    mlx_string_put(core->mlx, editwin->win, 330, 55, 0xFFFFFF, "Pos Z");
	mlx_string_put(core->mlx, editwin->win, 330, 105, 0xFFFFFF, "Pos Y");
	mlx_string_put(core->mlx, editwin->win, 330, 155, 0xFFFFFF, "Pos X");
	mlx_string_put(core->mlx, editwin->win, 130, 205, 0xFFFFFF, "Radius");
	mlx_string_put(core->mlx, editwin->win, 130, 255, 0xFFFFFF, "Height");
	mlx_mouse_hook(editwin->win, on_mouse_edit_c, editwin);
}
