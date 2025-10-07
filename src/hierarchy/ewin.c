/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ewin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:27:20 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:28:31 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hierarchy.h"
#include "mlx.h"

#include <stdlib.h>

/*
 * @brief Closes and frees the temporary edit window
 *
 * @details
 * Only accessed through the "Close" button, closing with the cross on
 * the mlx window seems to cause some issues for now.
 *
 * Core's prevent_close flag is used here to avoid closing miniRT
 * while the edit window is opened. Edit window(s) are not accessible
 * from core directly to avoid filling it with too much stuff.
*/
int	close_ewin(t_ewin *ewin)
{
	if (ewin->color_picker_img)
		mlx_destroy_image(ewin->core->mlx, ewin->color_picker_img);
	if (ewin->img.img)
		mlx_destroy_image(ewin->core->mlx, ewin->img.img);
	if (ewin->win)
		mlx_destroy_window(ewin->core->mlx, ewin->win);
	ewin->core->prevent_close -= 1;
	free(ewin);
	return (0);
}

/*
 * @brief Creates/Mallocs a new edit window
 *
 * @details
 * Assigns core, the wanted shape to edit, and prevents miniRT from closing.
 * Calls draw_ewin_rec() to draw all the needed rectangles.
 * mlx_string_put prints string after anything else as it would be overwritten
 * otherwise.
 * Calls mlx_mouse_hook allow click checks on the edit window.
*/
void	open_ewin(t_core *core, t_shape *shape)
{
	t_ewin	*ewin;

	ewin = malloc(sizeof(t_ewin));
	if (!ewin)
		return ;
	ewin->core = core;
	ewin->shape = shape;
	core->prevent_close += 1;
	ewin->win = mlx_new_window(
			core->mlx, EWIN_WIDTH, EWIN_HEIGHT, "Edit Shape");
	ewin->img.img = mlx_new_image(core->mlx, EWIN_WIDTH, EWIN_HEIGHT);
	ewin->img.addr = mlx_get_data_addr(ewin->img.img,
			&ewin->img.bpp, &ewin->img.line_len, &ewin->img.endian);
	if (shape->type == SPHERE)
		ewin_sphere(ewin);
	else if (shape->type == PLANE)
		ewin_plane(ewin);
	else if (shape->type == TRIANGLE)
		ewin_triangle(ewin);
	else
		ewin_cylinder(ewin);
}
