/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ewin_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:27:16 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:28:31 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>

int	on_mouse_edit_t(int button, int x, int y, void *param)
{
	t_ewin	*ewin;

	ewin = (t_ewin *)param;
	fetch_color_from_picker(x, y, ewin);
	if (button != 1)
		return (0);
	if (x >= 300 && x <= 380 && y >= 250 && y <= 280)
		return (close_ewin(ewin));
	return (0);
}

void	ewin_triangle(t_ewin *ewin)
{
	t_core	*core;

	core = get_core();
	draw_rect(
		&ewin->img, 0, 0, new_rec(EWIN_WIDTH, EWIN_HEIGHT, UI_BG_COLOR));
	draw_rect(&ewin->img, 300, 250, new_rec(80, 30, 0xCC3333));
	mlx_put_image_to_window(core->mlx, ewin->win, ewin->img.img, 0, 0);
	draw_color_picker(ewin, 250, 160);
	mlx_string_put(core->mlx, ewin->win, 320, 270, 0xFFFFFF, "Close");
	mlx_hook(ewin->win, ButtonPress, ButtonPressMask, on_mouse_edit_t, ewin);
}
