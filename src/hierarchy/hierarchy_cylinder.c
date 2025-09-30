#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>

void	apply_cyl_rad(t_ewin *ewin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 190 && y <= 220)
		ewin->shape->radius += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 190 && y <= 220)
		ewin->shape->radius -= 0.1f;
}

void	apply_cyl_dir(t_ewin *ewin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 40 && y <= 70)
		ewin->shape->direction.z += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 40 && y <= 70)
		ewin->shape->direction.z -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 90 && y <= 120)
		ewin->shape->direction.y += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 90 && y <= 120)
		ewin->shape->direction.y -= 0.1f;
	else if (x >= 50 && x <= 80 && y >= 140 && y <= 170)
		ewin->shape->direction.x += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 140 && y <= 170)
		ewin->shape->direction.x -= 0.1f;
}

void	apply_cyl_height(t_ewin *ewin, int x, int y)
{
	if (x >= 50 && x <= 80 && y >= 240 && y <= 270)
		ewin->shape->height += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 240 && y <= 270)
		ewin->shape->height -= 0.1f;
}

void	apply_cyl_pos(t_ewin *ewin, int x, int y)
{
	if (x >= 250 && x <= 280 && y >= 40 && y <= 70)
		ewin->shape->position.z += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 40 && y <= 70)
		ewin->shape->position.z -= 0.1f;
	else if (x >= 250 && x <= 280 && y >= 90 && y <= 120)
		ewin->shape->position.y += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 90 && y <= 120)
		ewin->shape->position.y -= 0.1f;
	else if (x >= 250 && x <= 280 && y >= 140 && y <= 170)
		ewin->shape->position.x += 0.1f;
	else if (x >= 290 && x <= 320 && y >= 140 && y <= 170)
		ewin->shape->position.x -= 0.1f;
}

int	on_mouse_edit_c(int button, int x, int y, void *param)
{
	t_ewin	*ewin;

	ewin = (t_ewin *)param;
	fetch_color_from_picker(x, y, ewin);
	if (button != 1)
		return (0);
	apply_cyl_pos(ewin, x, y);
	apply_cyl_rad(ewin, x, y);
	apply_cyl_dir(ewin, x, y);
	apply_cyl_height(ewin, x, y);
	if (x >= 300 && x <= 380 && y >= 250 && y <= 280)
		return (close_ewin(ewin));
	return (0);
}

/**
 * @brief Draws the edit window's individual buttons.
 * @details
 * Usually, each property of an object has a button to +1 and a button to -1
 * said property, so the drawing of buttons goes in pairs. The close button
 * and the background are unique, though.
 * In order, here are the buttons that get drawn:
 * Background, dir Z, dir Y, dir X, Pos Z, PosY, Pos X, Radius/Size, Height,
 * Close.
 */
void	draw_ewin_rec_c(t_ewin *ewin)
{
	draw_rect(&ewin->img, 0, 0, new_rec(EWIN_WIDTH, EWIN_HEIGHT, UI_BG_COLOR));
	draw_rect(&ewin->img, 50, 40, new_rec(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 90, 40, new_rec(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 50, 90, new_rec(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 90, 90, new_rec(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 50, 140, new_rec(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 90, 140, new_rec(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 250, 40, new_rec(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 290, 40, new_rec(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 250, 90, new_rec(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 290, 90, new_rec(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 250, 140, new_rec(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 290, 140, new_rec(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 50, 190, new_rec(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 90, 190, new_rec(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 50, 240, new_rec(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 90, 240, new_rec(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 300, 250, new_rec(80, 30, 0xCC3333));
}

void	ewin_cylinder(t_ewin *ewin)
{
	t_core	*core;

	core = get_core();
	draw_ewin_rec_c(ewin);
	mlx_put_image_to_window(core->mlx, ewin->win, ewin->img.img, 0, 0);
	draw_color_picker(ewin, 250, 180);
	mlx_string_put(core->mlx, ewin->win, 320, 270, 0xFFFFFF, "Close");
	mlx_string_put(core->mlx, ewin->win, 130, 55, 0xFFFFFF, "Dir Z");
	mlx_string_put(core->mlx, ewin->win, 130, 105, 0xFFFFFF, "Dir Y");
	mlx_string_put(core->mlx, ewin->win, 130, 155, 0xFFFFFF, "Dir X");
	mlx_string_put(core->mlx, ewin->win, 330, 55, 0xFFFFFF, "Pos Z");
	mlx_string_put(core->mlx, ewin->win, 330, 105, 0xFFFFFF, "Pos Y");
	mlx_string_put(core->mlx, ewin->win, 330, 155, 0xFFFFFF, "Pos X");
	mlx_string_put(core->mlx, ewin->win, 130, 205, 0xFFFFFF, "Radius");
	mlx_string_put(core->mlx, ewin->win, 130, 255, 0xFFFFFF, "Height");
	mlx_mouse_hook(ewin->win, on_mouse_edit_c, ewin);
}
