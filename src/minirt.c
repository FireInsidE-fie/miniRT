#include "minirt.h"
#include "mlx.h"

// Standard library //
#include <stdlib.h>
#include <stdio.h>

int	rt_kill(t_core *core)
{
	mlx_destroy_window(core->mlx, core->win);
	mlx_destroy_display(core->mlx);
	free(core->mlx);
	return (exit(0), 0);
}

int	main(void)
{
	printf("hewwo world\n");
	init_window();
	mlx_loop(get_core()->mlx);
}
