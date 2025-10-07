/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hierarchy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:27:25 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:28:31 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>

/*
 * @brief Draws the gray rectangle and the edit button for all shapes on the
 * current page
*/
void	draw_buttons(t_shape *shape, t_img *img, int start, int y_offset)
{
	int	i;

	i = 0;
	while (shape && i++ < start)
		shape = shape->next;
	i = 0;
	while (shape && i++ < MAX_PER_PAGE)
	{
		draw_rect(img, 0, y_offset, new_rec(400, 50, UI_BG_COLOR));
		draw_rect(img, 300, y_offset + 10, new_rec(80, 30, UI_DARK_GRAY));
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
	draw_buttons(shape, img, start, y_offset);
	draw_rect(img, 0, 600, new_rec(100, 15, UI_DARK_GRAY));
	draw_rect(img, 300, 600, new_rec(100, 15, UI_DARK_GRAY));
	mlx_put_image_to_window(core->mlx, core->altwin, img->img, 0, 0);
	mlx_string_put(core->mlx, core->altwin, 20, 612, 0xFFFFFF, "< Prev");
	mlx_string_put(core->mlx, core->altwin, 330, 612, 0xFFFFFF, "Next >");
	draw_edit_text(core, shape, y_offset);
}

/* Sadly placed here because of functions in file limits

	Prints the string of the wanted shape on the hierarchy menu
*/
void	shape_edit_text(t_core *core, t_shape *shape, int y_offset)
{
	if (shape->type == SPHERE)
		mlx_string_put(core->mlx, core->altwin,
			50, y_offset + 28, UI_TEXT_COLOR, "Sphere");
	else if (shape->type == PLANE)
		mlx_string_put(core->mlx, core->altwin,
			50, y_offset + 28, UI_TEXT_COLOR, "Plane");
	else if (shape->type == CYLINDER)
		mlx_string_put(core->mlx, core->altwin,
			50, y_offset + 28, UI_TEXT_COLOR, "Cylinder");
	else if (shape->type == CONE)
		mlx_string_put(core->mlx, core->altwin,
			50, y_offset + 28, UI_TEXT_COLOR, "Cone");
	else
		mlx_string_put(core->mlx, core->altwin,
			50, y_offset + 28, UI_TEXT_COLOR, "Triangle");
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
	t_core	*core;
	t_shape	*shape;
	int		i;
	int		index;

	(void)param;
	core = get_core();
	index = y / UI_SHAPE_HEIGHT;
	shape = core->scene.shapes;
	if (button == 1 && y >= 580)
		return (handle_page_click(x), 0);
	index = core->page_idx * MAX_PER_PAGE + (y / UI_SHAPE_HEIGHT);
	i = 0;
	while (shape && i++ < index)
		shape = shape->next;
	if (!shape)
		return (0);
	if (button == 1 && x >= 300 && x <= 380)
		return (open_ewin(core, shape), 0);
	render_shape_list(core);
	return (0);
}
