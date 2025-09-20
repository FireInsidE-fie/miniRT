#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Gets the raw data for a given pixel of the color picker.
 */
static int	fetch_color_picker_data(
	t_ewin *ewin, char **data, int mouse_x, int mouse_y)
{
	int	bpp;
	int	line_len;
	int	endian;
	int	px;
	int	py;

	*data = mlx_get_data_addr(
			ewin->color_picker_img, &bpp, &line_len, &endian);
	px = mouse_x - ewin->cp_x;
	py = mouse_y - ewin->cp_y;
	return (py * line_len + px * (bpp / 8));
}

/**
 * @brief For a given edit window and position on the color picker,
 * set the edit window's associated object to the color found at that position.
 */
void	fetch_color_from_picker(int mouse_x, int mouse_y, t_ewin *ewin)
{
	char	*data;
	int		offset;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	data = NULL;
	offset = fetch_color_picker_data(ewin, &data, mouse_x, mouse_y);
	if (!ewin->color_picker_img)
		return ;
	if (mouse_x < ewin->cp_x
		|| mouse_x >= ewin->cp_x + ewin->cp_w
		|| mouse_y < ewin->cp_y
		|| mouse_y >= ewin->cp_y + ewin->cp_h)
		return ;
	b = data[offset + 0];
	g = data[offset + 1];
	r = data[offset + 2];
	ewin->shape->mat.color = (t_color){r / 255.0f, g / 255.0f, b / 255.0f};
	return ;
}

void	draw_color_picker(t_ewin *ewin, int x, int y)
{
	t_core	*core;

	ewin->cp_x = x;
	ewin->cp_y = y;
	core = get_core();
	ewin->color_picker_img = mlx_xpm_file_to_image(
			core->mlx, "src/hierarchy/8_1_.xpm", &ewin->cp_w, &ewin->cp_h
			);
	if (!ewin->color_picker_img)
		printf("Failed to open Color picker image.\n");
	mlx_put_image_to_window(
		core->mlx, ewin->win, ewin->color_picker_img,
		ewin->cp_x, ewin->cp_y);
}
