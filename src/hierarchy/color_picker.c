#include "minirt.h"
#include "mlx.h"
#include "hierarchy.h"

#include <X11/X.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* 
	Yes double pointer for char **data, i think the mlx wants "a pointer to", so even
	though it's already a pointer it will just invalid read if just sending char *data
	to another function..
*/
static int fetch_color_picker_data(t_ewin *editwin, char **data, int mouse_x, int mouse_y)
{
    int bpp;
    int line_len;
    int endian;
    int px;
    int py;

    *data = mlx_get_data_addr(editwin->color_picker_img, &bpp, &line_len, &endian);
    px = mouse_x - editwin->cp_x;
    py = mouse_y - editwin->cp_y;
    return (py * line_len + px * (bpp / 8));
}

void fetch_color_from_picker(int mouse_x, int mouse_y, t_ewin *editwin)
{
    char    *data;
    int     offset;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
    data = NULL;
    offset = fetch_color_picker_data(editwin, &data, mouse_x, mouse_y);
    if (!editwin->color_picker_img)
        return ;
    if (mouse_x < editwin->cp_x || mouse_x >= editwin->cp_x + editwin->cp_w || mouse_y < editwin->cp_y || mouse_y >= editwin->cp_y + editwin->cp_h)
        return ;
    b = data[offset + 0];
    g = data[offset + 1];
    r = data[offset + 2];
    editwin->shape->mat.color = (t_color){r / 255.0f, g / 255.0f, b / 255.0f};
    return ;
}


void	draw_color_picker(t_ewin *editwin, int x, int y)
{
	t_core	*core;

	editwin->cp_x = x;
	editwin->cp_y = y;
	core = get_core();
	editwin->color_picker_img = mlx_xpm_file_to_image(core->mlx, "src/hierarchy/8_1_.xpm", &editwin->cp_w, &editwin->cp_h);
	if (!editwin->color_picker_img)
		printf("Failed to open Color picker image.\n");
	mlx_put_image_to_window(core->mlx, editwin->win, editwin->color_picker_img, editwin->cp_x, editwin->cp_y);
}
