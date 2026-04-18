#include "../includes/cub3d.h"
#include <stdio.h>

void	print_cub_debug(t_cub *cub)
{
	int	i;

	printf("=== CUB3D PARSER DEBUG ===\n");
	printf("NO Path: [%s]\n", cub->no_path ? cub->no_path : "NULL");
	printf("SO Path: [%s]\n", cub->so_path ? cub->so_path : "NULL");
	printf("WE Path: [%s]\n", cub->we_path ? cub->we_path : "NULL");
	printf("EA Path: [%s]\n", cub->ea_path ? cub->ea_path : "NULL");
	
	// Print colors in Hex so you can easily see the RGB channels
	printf("Floor Color:   [0x%06X]\n", cub->floor_color);
	printf("Ceiling Color: [0x%06X]\n", cub->ceiling_color);
	printf("\n=== MAP INFO ===\n");
	printf("Width: %d\n", cub->map.width);
	printf("Height: %d\n", cub->map.height);
	printf("Player Count: %d\n", cub->map.player_count);
	
	printf("\n=== MAP GRID ===\n");
	i = 0;
	while (i < cub->map.height)
	{
		// Printing between pipes to visually see padding/spaces at the edges
		printf("|%s|\n", cub->map.grid[i]);
		i++;
	}
	printf("==========================\n");
}