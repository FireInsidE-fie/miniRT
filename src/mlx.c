#include "minirt.h"
#include "mlx.h"

t_core	*get_core(void)
{
	static t_core	core;

	if (!core.mlx)
		core.mlx = mlx_init();
	return (&core);
}

static void	init_hooks(t_core *core)
{
	core = get_core();
	// TODO: Hook for pressing `q` ending program
	// mlx_hook(core->win, 2, 0, key_press, core);
	mlx_hook(core->win, 17, 0, rt_kill, core);
}

/**
 * @brief Creates the MLX window.
 *
 * @return 0 if all went well, 1 if window initialization failed.
 */
int	init_window(void)
{
	t_core	*core;

	core = get_core();
	core->win
		= mlx_new_window(core->mlx, WIN_WIDTH, WIN_HEIGHT, "Obsolete Meat");
	if (!core->win)
		return (1);
	return (0);
}
