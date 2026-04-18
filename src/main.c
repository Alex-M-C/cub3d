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
}

/*
** Placeholder for where raycasting logic begins.
*/
/*
static void	run_game(t_cub *cub)
{
	// 1. Initialize mlx: cub->mlx = mlx_init();
	// 2. Open window: cub->win = mlx_new_window(...);
	// 3. Convert NO, SO, WE, EA paths into mlx images.
	// 4. Set up mlx_hook for keys (WASD, arrows, ESC).
	// 5. Start the render loop: mlx_loop_hook(...);
	// 6. mlx_loop(cub->mlx);
	
	(void)cub; // Suppress unused variable warning for now
	printf("Map and config loaded successfully! Starting game...\n");
}
*/

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
	// run_game(&cub);
    print_cub_debug(&cub);
    free_cub(&cub);
	return (0);
}
