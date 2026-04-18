#include "../includes/cub3d.h"

/*
** Safely frees all allocated memory inside the main structure.
*/
void	free_cub(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	if (cub->no_path)
		free(cub->no_path);
	if (cub->so_path)
		free(cub->so_path);
	if (cub->we_path)
		free(cub->we_path);
	if (cub->ea_path)
		free(cub->ea_path);
	if (cub->map.grid)
	{
		i = 0;
		while (i < cub->map.height)
		{
			if (cub->map.grid[i])
				free(cub->map.grid[i]);
			i++;
		}
		free(cub->map.grid);
	}
}

/*
** Prints the given error message to STDERR, frees resources, and exits.
*/
void	err_exit(t_cub *cub, char *message)
{
	if (message)
	{
		// Printing to file descriptor 2 (STDERR)
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (cub)
		free_cub(cub);
	exit(1);
}