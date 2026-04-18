#include "../includes/cub3d.h"

/*
** Dynamically increases the 2D char array to hold the newly read line.
*/
static char	**grow_grid(char **old_grid, int old_height, char *new_line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (old_height + 2));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < old_height)
	{
		new_grid[i] = old_grid[i];
		i++;
	}
	new_grid[i] = ft_strdup(new_line);
	new_grid[i + 1] = NULL;
	free(old_grid);
	return (new_grid);
}

/*
** Appends a single line to the map grid.
*/
void	extract_map_line(char *line, t_cub *cub)
{
	cub->map.grid = grow_grid(cub->map.grid, cub->map.height, line);
	if (!cub->map.grid)
	{
		free(line);
		err_exit(cub, "Error\nMalloc failed during map extraction");
	}
	cub->map.height++;
}

static void	calculate_max_width(t_map *map)
{
	int	i;
	int	current_len;

	map->width = 0;
	i = 0;
	while (i < map->height)
	{
		current_len = ft_strlen(map->grid[i]);
		if (current_len > map->width)
			map->width = current_len;
		i++;
	}
}

void	pad_map(t_cub *cub)
{
	int		i;
	int		j;
	int		len;
	char	*padded;

	i = -1;
	calculate_max_width(&cub->map);
	while (++i < cub->map.height)
	{
		len = ft_strlen(cub->map.grid[i]);
		if (len < cub->map.width)
		{
			padded = malloc(sizeof(char) * (cub->map.width + 1));
			if (!padded)
				err_exit(cub, "Error\nMalloc failed during map padding");
			ft_strlcpy(padded, cub->map.grid[i], len + 1);
			j = len;
			while (j < cub->map.width)
				padded[j++] = ' ';
			padded[cub->map.width] = '\0';
			free(cub->map.grid[i]);
			cub->map.grid[i] = padded;
		}
	}
}

