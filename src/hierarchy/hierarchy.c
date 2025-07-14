#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>

#define UI_SHAPE_HEIGHT 50
#define MAX_PER_PAGE 12

// list size but for t_shape type

int	shape_lst_size(t_shape *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// Used this instead of the color struct to test out Hex codes faster.

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/* Creates a rectangle struct, quite simple to understand i hope.
*/

t_rectangle	new_rectangle(int width, int height, int color)
{
	t_rectangle	rec;

	rec.width = width;
	rec.height = height;
	rec.color = color;
	return (rec);
}

// Draws a rectangle with a given img, coordinates and t_rectangle.
// t_rectangle structs contain : int width, int height, int color (hex)

void	draw_rect(t_img *img, int x, int y, t_rectangle rec)
{
	int	i;
	int	j;

	i = y;
	while (i < y + rec.height)
	{
		j = x;
		while (j < x + rec.width)
		{
			my_mlx_pixel_put(img, j, i, rec.color);
			j++;
		}
		i++;
	}
}

// Draws the gray rectangle and the edit button per shape 

void	draw_button(t_shape *shape, t_img *img, int start, int y_offset)
{
	int	i;

	i = 0;
	while (shape && i++ < start)
		shape = shape->next;
	i = 0;
	while (shape && i++ < MAX_PER_PAGE)
	{
		draw_rect(img, 0, y_offset, new_rectangle(400, 50, 0x343434));
		draw_rect(img, 300, y_offset + 10, new_rectangle(80, 30, 0x555555));
		y_offset += 50;
		shape = shape->next;
	}
}

/* Creates the ui_img image and calls every function that reprints
	elements of the UI.

	if core->ui_img_init is set, destroys the window and redoes it.
	This avoids still reachable leaks from the UI.

	render_shape_list() is first called on startup. It is also recalled
	when changes are made, such as changing pages or even clicking
	anywhere on the ui, this last case fixes a specific issue where
	the window would appear pitch back when resized.
*/ 

void	render_shape_list(t_core *core)
{
	t_shape		*shape;
	int			y_offset;
	int			start;
	t_img		*img;

	img = &core->ui_img;
	if (core->ui_img_init)
		mlx_destroy_image(core->mlx, img->img);
	img->img = mlx_new_image(core->mlx, 400, 615);
	img->addr
		= mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	core->ui_img_init = 1;
	start = core->page_idx * MAX_PER_PAGE;
	shape = core->scene.shapes;
	y_offset = 0;
	draw_button(shape, img, start, y_offset);
	draw_rect(img, 0, 600, new_rectangle(100, 15, 0x555555));
	draw_rect(img, 300, 600, new_rectangle(100, 15, 0x555555));
	mlx_put_image_to_window(core->mlx, core->altwin, img->img, 0, 0);
	mlx_string_put(core->mlx, core->altwin, 20, 612, 0xFFFFFF, "< Prev");
	mlx_string_put(core->mlx, core->altwin, 330, 612, 0xFFFFFF, "Next >");
	draw_edit_text(core, shape, y_offset);
}

/* Main Mouse Hook for the Hierarchy

	if core->ui_img_init is set, destroys the window and redoes it.
	This avoids still reachable leaks from the UI.

	render_shape_list() is first called on startup. It is also recalled
	when changes are made, such as changing pages or even clicking
	anywhere on the ui, this fixes a specific issue where the window
	would appear pitch back when resized.

*/ 

int	on_mouse_debug(int button, int x, int y, void *param)
{
	t_shape	*shape;
	int		i;
	int		index;
	int		block_height;

	(void)param;
	block_height = 50;
	index = y / block_height;
	shape = get_core()->scene.shapes;
	if (y >= 580)
		return (handle_page_click(x), 0);
	index = get_core()->page_idx * MAX_PER_PAGE + (y / block_height);
	i = 0;
	while (shape && i++ < index)
		shape = shape->next;
	if (!shape)
		return (0);
	if (button == 1)
	{
		if (x >= 300 && x <= 380)
			return (open_edit_window(get_core(), shape), 0);
	}
	render_shape_list(get_core());
	return (0);
}
