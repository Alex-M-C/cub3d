/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:59 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/05 19:24:38 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Safely initializes the main structure to prevent reading garbage memory.
*/
static void	init_cub(t_cub *cub)
{
	cub->no_path = NULL;
	cub->so_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	cub->elements_found = 0;
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.player_count = 0;
	cub->player.x = 0.0;
	cub->player.y = 0.0;
	cub->player.dir_x = 0.0;
	cub->player.dir_y = 0.0;
	cub->player.plane_x = 0.0;
	cub->player.plane_y = 0.0;
	cub->keys.w = 0;
	cub->keys.a = 0;
	cub->keys.s = 0;
	cub->keys.d = 0;
	cub->keys.left = 0;
	cub->keys.right = 0;
}

static void	load_texture(t_cub *cub, int index, char *path)
{
	cub->textures[index].img_ptr = mlx_xpm_file_to_image(cub->mlx, path,
			&cub->textures[index].width,
			&cub->textures[index].height);
	if (!cub->textures[index].img_ptr)
		err_exit(cub, "Error\nFailed to load texture");
	cub->textures[index].addr = mlx_get_data_addr(cub->textures[index].img_ptr,
			&cub->textures[index].bpp,
			&cub->textures[index].line_length,
			&cub->textures[index].endian);
}

/*
** 1. Initialize mlx: cub->mlx = mlx_init();
** 2. Open window: cub->win = mlx_new_window(...);
** 3. Convert NO, SO, WE, EA paths into mlx images.
** 4. Set up mlx_hook for keys (WASD, arrows, ESC).
** 5. Start the render loop: mlx_loop_hook(...);
** 6. mlx_loop(cub->mlx);
*/
static void	run_game(t_cub *cub)
{
	if (create_window(cub))
	{
		ft_printf("Error: can't create window\n");
		return ;
	}
	cub->screen.img_ptr = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->screen.addr = mlx_get_data_addr(cub->screen.img_ptr,
			&cub->screen.bpp,
			&cub->screen.line_length,
			&cub->screen.endian);
	load_texture(cub, NO, cub->no_path);
	load_texture(cub, SO, cub->so_path);
	load_texture(cub, EA, cub->ea_path);
	load_texture(cub, WE, cub->we_path);
	ft_printf("Map and config loaded successfully! Starting game...\n");
	raycast_loop(cub);
	mlx_hook(cub->win, 2, 1L << 0, handle_key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, handle_key_release, cub);
	mlx_hook(cub->win, 17, 0, close_window, cub);
	mlx_loop_hook(cub->mlx, handle_move, cub);
	mlx_loop(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cub;
	int		fd;

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D <path_to_map.cub>\n", 39);
		return (1);
	}
	check_file_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCould not open file\n", 26);
		return (1);
	}
	init_cub(&cub);
	parse_file(fd, &cub);
	close(fd);
	pad_map(&cub);
	validate_cub_map(&cub);
	run_game(&cub);
	print_cub_debug(&cub);
	free_cub(&cub);
	return (0);
}
