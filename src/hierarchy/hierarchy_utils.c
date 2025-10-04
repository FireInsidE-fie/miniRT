#include "mlx.h"
#include "utils.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Computes the size of a linked list of `t_shape`s.
 */
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

t_rectangle	new_rec(int width, int height, int color)
{
	t_rectangle	rec;

	rec.width = width;
	rec.height = height;
	rec.color = color;
	return (rec);
}

/*
 * @brief Draws a rectangle with a given img, coordinates and t_rectangle.
*/
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
			img_put_pixel(img, j, i, rec.color);
			j++;
		}
		i++;
	}
}

/*
 * @brief Hard prints "Edit" and t_shape type on the Hierarchy window
 *
 * @details
 * The first while loops will advance in the t_shape list to reach
 * the current page/shape and print text for the right shapes.
 * once at the right index, it will print the wanted page, up to 12 shapes.
 * We hard print those pieces of text after any other render, or the text
 * would get overwritten by rectangles. mlx_string_put doesn't require frees.
*/
void	draw_edit_text(t_core *core, t_shape *shape, int y_offset)
{
	int	i;

	i = 0;
	while (shape && i++ < core->page_idx * MAX_PER_PAGE)
		shape = shape->next;
	i = 0;
	while (shape && i++ < MAX_PER_PAGE)
	{
		shape_edit_text(core, shape, y_offset);
		mlx_string_put(core->mlx, core->altwin,
			320, y_offset + 28, UI_TEXT_COLOR, "Edit");
		y_offset += 50;
		shape = shape->next;
	}
}

/*
 * @brief Checks if a page button was pressed
 *
 * @details
 * Increments or decrements the page if x is in the range up to max_page.
 *
 * 38 shapes would have a max_page of 3 (printed as 4 on the printf).
 * Pages 0 to 2 would have 12 shapes and page 3 would have 2 shapes.
 * once edited, rerender with render_shape_list()
*/
void	handle_page_click(int x)
{
	int		max_page;
	t_core	*core;

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
