/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrey <nrey@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:28:25 by nrey              #+#    #+#             */
/*   Updated: 2025/10/07 14:28:31 by nrey             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "scene.h"
#include "light.h"
#include "libft.h"
#include "parsing.h"
#include "utils.h"
#include "textures.h"

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/**
 * @brief The "core" struct of the program contains MLX-related data, the scene
 * and the mlx image the render is going to be written to.
 * @see The `minirt.h` file for the struct itself.
 */
t_core	*get_core(void)
{
	static t_core	core;

	return (&core);
}

/**
 * @brief Closes the program and cleans its heap-allocated memory.
 * Also takes care of MLX ressources.
 */
int	rt_kill(int exit_code)
{
	t_core	*core;

	core = get_core();
	if (core->prevent_close)
		return (printf("[!] - Close edit Window before quitting\n"), 0);
	printf("[!] - Closing miniRT...\n");
	clear_lights(core->scene.lights);
	clear_shapes(core->scene.shapes);
	if (core->mlx)
	{
		mlx_destroy_image(core->mlx, core->img.img);
		mlx_destroy_image(core->mlx, core->ui_img.img);
		mlx_destroy_window(core->mlx, core->altwin);
		mlx_destroy_window(core->mlx, core->win);
		load_earth_texture(FREE);
		load_moon_texture(FREE);
		load_earth_bumpmap(FREE);
		load_moon_bumpmap(FREE);
		mlx_destroy_display(core->mlx);
		free(core->mlx);
	}
	return (exit(exit_code), exit_code);
}

int	main(int argc, char **argv)
{
	t_core	*core;
	int		parse_status;
	int		scene_fd;

	if (argc != 2)
		return (printf("Usage: ./miniRT <path_to_map>\n"), 1);
	if (check_path(argv[1]) == false)
		return (print_ps(FILE_ERR, 0));
	core = get_core();
	ft_bzero(core, sizeof(t_core));
	default_camera(&core->scene.camera);
	scene_fd = open(argv[1], O_DIRECTORY);
	if (scene_fd != -1)
		return (close(scene_fd), printf("[!] - Provided path is a dir!\n"), 1);
	scene_fd = open(argv[1], O_RDONLY);
	if (scene_fd == -1)
		return (perror("miniRT - parse_scene (open)"), print_ps(OPEN_ERR, 0));
	parse_status = parse_scene(scene_fd);
	if (parse_status != 0)
		return (rt_kill(parse_status));
	print_scene(&core->scene);
	init_window();
	printf("================\n");
}
