#include "minirt.h"
#include "mlx.h"

t_mlx	*get_graphics(void)
{
	static t_mlx	graphics;

	if (!graphics.mlx)
		graphics.mlx = mlx_init();
	return (&graphics);
}

/**
 * @brief Creates the MLX window.
 *
 * @return 0 if all went well, 1 if window initialization failed.
 */
int	init_window(void)
{
	t_mlx	*graphics;

	graphics = get_graphics();
	graphics->win
		= mlx_new_window(graphics->mlx, WIN_WIDTH, WIN_HEIGHT, "Obsolete Meat");
	if (!graphics->win)
		return (1);
	return (0);
}
