#include "minirt.h"
#include "mlx.h"

#include <stdio.h>

int	main(void)
{
	printf("hewwo world\n");
	init_window();
	mlx_loop(get_graphics()->mlx);
}
