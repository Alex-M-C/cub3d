#include "../includes/cub3d.h"

/*
** Checks if characters are valid and counts the player entities.
*/
static int	check_chars_and_player(t_map *map)
{
	int	x;
	int	y;

	map->player_count = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->grid[y][++x])
		{
			if (!ft_strchr("01 NSEW", map->grid[y][x]))
				return (0);
			if (ft_strchr("NSEW", map->grid[y][x]))
				map->player_count++;
		}
	}
	if (map->player_count != 1)
		return (0);
	return (1);
}

/*
** Verifies if a specific floor/player cell is fully enclosed by walls or floor.
*/
static int	is_enclosed(t_map *map, int y, int x)
{
	int	len_above;
	int	len_below;

	if (y == 0 || y == map->height - 1 || x == 0)
		return (0);
	if (x >= (int)ft_strlen(map->grid[y]) - 1)
		return (0);
	len_above = ft_strlen(map->grid[y - 1]);
	len_below = ft_strlen(map->grid[y + 1]);
	if (x >= len_above || map->grid[y - 1][x] == ' ')
		return (0);
	if (x >= len_below || map->grid[y + 1][x] == ' ')
		return (0);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

/*
** Iterates through the map to ensure no '0' or player touches the void.
*/
static int	check_walls(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (map->grid[y][++x])
		{
			if (ft_strchr("0NSEW", map->grid[y][x]))
			{
				if (!is_enclosed(map, y, x))
					return (0);
			}
		}
	}
	return (1);
}

void	validate_cub_map(t_cub *cub)
{
	if (!check_chars_and_player(&cub->map))
		err_exit(cub, "Error\nInvalid map characters or wrong player count");
	if (!check_walls(&cub->map))
		err_exit(cub, "Error\nMap is not enclosed by walls");
}