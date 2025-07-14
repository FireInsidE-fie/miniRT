#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UI_SHAPE_HEIGHT 50
#define MAX_PER_PAGE 12

/* Closes and frees the temporary edit window

	Only accessed through the "Close" button, closing with the cross on
	the mlx window seems to cause some issues for now.

	Core's prevent_close flag is used here to avoid closing miniRT
	while the edit window is opened. Edit window(s) are not accessible
	from core directly to avoid filling it with too much stuff.
*/ 

int	close_edit_window(t_edit_win *editwin)
{
	if (editwin->img.img)
		mlx_destroy_image(editwin->core->mlx, editwin->img.img);
	if (editwin->win)
		mlx_destroy_window(editwin->core->mlx, editwin->win);
	editwin->core->prevent_close = 0;
	free(editwin);
	return (0);
}

/* Mouse hook called in open_edit_window when an edit window is opened.

	Checks for the area clicked, matches the colored
	red and green squares buttons.
*/ 

int	on_mouse_edit(int button, int x, int y, void *param)
{
	t_edit_win	*editwin;

	editwin = (t_edit_win *)param;
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

/* Draws colored rectangles for the Edit window

	First one is the overall window background color.
	Last one is the Close button.
	everything in between is the red and green action buttons.
*/ 

void	draw_edit_win_rec(t_edit_win *editwin)
{
	draw_rect(&editwin->img, 0, 0, new_rectangle(400, 300, 0x343434));
	draw_rect(&editwin->img, 50, 40, new_rectangle(30, 30, 0x56fc61));
	draw_rect(&editwin->img, 90, 40, new_rectangle(30, 30, 0xfc5656));
	draw_rect(&editwin->img, 50, 90, new_rectangle(30, 30, 0x56fc61));
	draw_rect(&editwin->img, 90, 90, new_rectangle(30, 30, 0xfc5656));
	draw_rect(&editwin->img, 50, 140, new_rectangle(30, 30, 0x56fc61));
	draw_rect(&editwin->img, 90, 140, new_rectangle(30, 30, 0xfc5656));
	draw_rect(&editwin->img, 50, 190, new_rectangle(30, 30, 0x56fc61));
	draw_rect(&editwin->img, 90, 190, new_rectangle(30, 30, 0xfc5656));
	draw_rect(&editwin->img, 300, 250, new_rectangle(80, 30, 0xCC3333));
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
	t_edit_win	*editwin;

	editwin = malloc(sizeof(t_edit_win));
	if (!editwin)
		return ;
	editwin->core = core;
	editwin->shape = shape;
	core->prevent_close = 1;
	editwin->win = mlx_new_window(core->mlx, 400, 300, "Edit Shape");
	editwin->img.img = mlx_new_image(core->mlx, 400, 300);
	editwin->img.addr = mlx_get_data_addr(editwin->img.img,
			&editwin->img.bpp, &editwin->img.line_len, &editwin->img.endian);
	draw_edit_win_rec(editwin);
	mlx_put_image_to_window(core->mlx, editwin->win, editwin->img.img, 0, 0);
	mlx_string_put(core->mlx, editwin->win, 320, 270, 0xFFFFFF, "Close");
	mlx_string_put(core->mlx, editwin->win, 130, 155, 0xFFFFFF, "X Axis");
	mlx_string_put(core->mlx, editwin->win, 130, 105, 0xFFFFFF, "Y Axis");
	mlx_string_put(core->mlx, editwin->win, 130, 55, 0xFFFFFF, "Z Axis");
	mlx_string_put(core->mlx, editwin->win, 130, 205, 0xFFFFFF, "Size/Radius");
	mlx_mouse_hook(editwin->win, on_mouse_edit, editwin);
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

	max_page = (shape_lst_size(get_core()->scene.shapes) - 1) / MAX_PER_PAGE;
	if (x >= 0 && x <= 100 && get_core()->page_idx > 0)
		get_core()->page_idx--;
	else if (x >= 300 && x <= 400 && get_core()->page_idx < max_page)
		get_core()->page_idx++;
	printf("Page %d/%d\n", get_core()->page_idx + 1,
		(shape_lst_size(get_core()->scene.shapes) / MAX_PER_PAGE) + 1);
	render_shape_list(get_core());
}
