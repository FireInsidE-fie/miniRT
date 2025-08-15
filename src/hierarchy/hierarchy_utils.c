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

/* Closes and frees the temporary edit window

	Only accessed through the "Close" button, closing with the cross on
	the mlx window seems to cause some issues for now.

	Core's prevent_close flag is used here to avoid closing miniRT
	while the edit window is opened. Edit window(s) are not accessible
	from core directly to avoid filling it with too much stuff.
*/

int	close_edit_window(t_ewin *editwin)
{
	if (editwin->img.img)
		mlx_destroy_image(editwin->core->mlx, editwin->img.img);
	if (editwin->win)
		mlx_destroy_window(editwin->core->mlx, editwin->win);
	editwin->core->prevent_close -= 1;
	free(editwin);
	return (0);
}

/* Creates/Mallocs a new edit window

	Assigns core, the wanted shape to edit, and prevents miniRT from closing.

	Calls draw_edit_win_rec() to draw all the needed rectangles.

	mlx_string_put prints string after anything else as it would be overwritten
	otherwise.

	Calls mlx_mouse_hook allow click checks on the edit window.
*/

void	open_edit_window(t_core *core, t_shape *shape)
{
	t_ewin	*editwin;

	editwin = malloc(sizeof(t_ewin));
	if (!editwin)
		return ;
	editwin->core = core;
	editwin->shape = shape;
	core->prevent_close += 1;
	editwin->win = mlx_new_window(core->mlx, EWIN_WIDTH, EWIN_HEIGHT, "Edit Shape");
	editwin->img.img = mlx_new_image(core->mlx, EWIN_WIDTH, EWIN_HEIGHT);
	editwin->img.addr = mlx_get_data_addr(editwin->img.img,
			&editwin->img.bpp, &editwin->img.line_len, &editwin->img.endian);
	if (shape->type == SPHERE)
		edit_win_sphere(editwin);
	else if (shape->type == PLANE)
		edit_win_plane(editwin);
	else
		edit_win_cylinder(editwin);

}

/* Hard prints "Edit" and t_shape type on the Hierarchy window

	The first while loops will advance in the t_shape list to reach
	the current page/shape and print text for the right shapes.

	once at the right index, it will print the wanted page, up to 12 shapes.

	We hard print those pieces of text after any other render, or the text
	would get overwritten by rectangles. mlx_string_put doesn't require frees.
*/

void	draw_edit_text(t_core *core, t_shape *shape, int y_offset)
{
	int	i;
	int	start;

	start = core->page_idx * MAX_PER_PAGE;
	i = 0;
	while (shape && i++ < start)
		shape = shape->next;
	i = 0;
	while (shape && i++ < MAX_PER_PAGE)
	{
		mlx_string_put(core->mlx, core->altwin,
			320, y_offset + 28, 0xFFFFFF, "Edit");
		if (shape->type == SPHERE)
			mlx_string_put(core->mlx, core->altwin,
				50, y_offset + 28, 0xFFFFFF, "Sphere");
		else if (shape->type == PLANE)
			mlx_string_put(core->mlx, core->altwin,
				50, y_offset + 28, 0xFFFFFF, "Plane");
		else if (shape->type == CYLINDER)
			mlx_string_put(core->mlx, core->altwin,
				50, y_offset + 28, 0xFFFFFF, "Cylinder");
		y_offset += 50;
		shape = shape->next;
	}
}

/* Checks if a page button was pressed

	Increments or decrements the page if x is in the range up to max_page.

	38 shapes would have a max_page of 3 (printed as 4 on the printf).
	Pages 0 to 2 would have 12 shapes and page 3 would have 2 shapes.

	once edited, rerender with render_shape_list()
*/

void	handle_page_click(int x)
{
	int	max_page;
	t_core *core;

	core = get_core();
	max_page = (shape_lst_size(core->scene.shapes) - 1) / MAX_PER_PAGE;
	if (x >= 0 && x <= 100 && core->page_idx > 0)
		core->page_idx--;
	else if (x >= 300 && x <= 400 && core->page_idx < max_page)
		core->page_idx++;
	printf("Page %d/%d\n", core->page_idx + 1,
		(shape_lst_size(core->scene.shapes) / MAX_PER_PAGE) + 1);
	render_shape_list(core);
}
