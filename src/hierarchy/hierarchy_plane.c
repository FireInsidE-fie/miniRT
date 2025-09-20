#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>

/* Mouse hook called in ewin_plane when an edit window is opened.
 * Checks for the area clicked, matches the colored
 * red and green squares buttons.
 */
int	on_mouse_edit_p(int button, int x, int y, void *param)
{
	t_ewin	*ewin;

	ewin = (t_ewin *)param;
	fetch_color_from_picker(x, y, ewin);
	if (button != 1)
		return (0);
	if (x >= 50 && x <= 80 && y >= 40 && y <= 70)
		ewin->shape->position.y += 0.1f;
	else if (x >= 90 && x <= 120 && y >= 40 && y <= 70)
		ewin->shape->position.y -= 0.1f;
	else if (x >= 300 && x <= 380 && y >= 250 && y <= 280)
		return (close_ewin(ewin));
	return (0);
}

/*
	Draws colored rectangles for the Edit window for Plane editing
*/

void	draw_ewin_rec_p(t_ewin *ewin)
{
	draw_rect(&ewin->img, 0, 0, new_rectangle(EWIN_WIDTH, EWIN_HEIGHT, UI_BG_COLOR));
	draw_rect(&ewin->img, 50, 40, new_rectangle(EWIN_B, EWIN_B, EWIN_GREEN));
	draw_rect(&ewin->img, 90, 40, new_rectangle(EWIN_B, EWIN_B, EWIN_RED));
	draw_rect(&ewin->img, 300, 250, new_rectangle(80, 30, 0xCC3333));
}

void	ewin_plane(t_ewin *ewin)
{
	t_core	*core;

	core = get_core();
	draw_ewin_rec_p(ewin);
	mlx_put_image_to_window(core->mlx, ewin->win, ewin->img.img, 0, 0);
	draw_color_picker(ewin, 250, 160);
	mlx_string_put(core->mlx, ewin->win, 320, 270, 0xFFFFFF, "Close");
	mlx_string_put(core->mlx, ewin->win, 130, 55, 0xFFFFFF, "Y Axis");
	mlx_mouse_hook(ewin->win, on_mouse_edit_p, ewin);
}
