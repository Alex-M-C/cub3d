#include "../includes/cub3d.h"

void	check_file_extension(const char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
	{
		write(2, "Error\nMap file format must be .cub\n", 35);
		exit(1);
	}
}

/*
** Checks if the line only contains whitespaces or a newline
*/
static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i] == '\0');
}

/*
** Removes the newline character at the end of the line if it exists.
*/
static void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

void	parse_file(int fd, t_cub *cub)
{
	char	*line;
    int		map_ended;

    map_ended = 0;
	cub->elements_found = 0;
	line = get_next_line(fd);
	while (line)
	{
        trim_newline(line);
		if (cub->elements_found < 6)
		{
			if (!is_empty_line(line) && !parse_element(line, cub))
			{
				free(line);
				err_exit(cub, "Error\nInvalid element or map started too early");
			}
		}
		else
		{
			if (is_empty_line(line))
			{
				if (cub->map.height > 0)
					map_ended = 1;
			}
			else
			{
				if (map_ended)
				{
					free(line);
					err_exit(cub, "Error\nEmpty line inside the map content");
				}
				extract_map_line(line, cub);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
}
