#include "../includes/cub3d.h"

/*
** Extracts the texture path.
*/
static int	extract_texture(char **path, char *line)
{
	int	i;

	if (*path != NULL)
		return (0);
	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (0);
	*path = ft_strdup(&line[i]);
	return (1);
}

/*
** Parses a single RGB value (0-255) and advances the string pointer.
*/
static int	get_color_val(char **s)
{
	int	val;
	int	len;

	val = 0;
	len = 0;
	while (**s == ' ' || **s == '\t')
		(*s)++;
	if (!ft_isdigit(**s))
		return (-1);
	while (ft_isdigit(**s))
	{
		val = val * 10 + (**s - '0');
		(*s)++;
		len++;
	}
	if (len > 3 || val > 255)
		return (-1);
	while (**s == ' ' || **s == '\t')
		(*s)++;
	return (val);
}

/*
** Extracts the R, G, B color integers and shifts them into a single int.
*/
static int	extract_color(int *color, char *line)
{
	int		r;
	int		g;
	int		b;
	char	*ptr;

	if (*color != -1)
		return (0);
	ptr = line + 1;
	r = get_color_val(&ptr);
	if (r == -1 || *ptr != ',')
		return (0);
	ptr++;
	g = get_color_val(&ptr);
	if (g == -1 || *ptr != ',')
		return (0);
	ptr++;
	b = get_color_val(&ptr);
	if (b == -1 || *ptr != '\0')
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

/*
** Routes the line to the correct extraction function based on the identifier.
*/
int	parse_element(char *line, t_cub *cub)
{
	int	success;

	success = 0;
	if (ft_strncmp(line, "NO ", 3) == 0)
		success = extract_texture(&cub->no_path, line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		success = extract_texture(&cub->so_path, line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		success = extract_texture(&cub->we_path, line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		success = extract_texture(&cub->ea_path, line);
	else if (ft_strncmp(line, "F ", 2) == 0)
		success = extract_color(&cub->floor_color, line);
	else if (ft_strncmp(line, "C ", 2) == 0)
		success = extract_color(&cub->ceiling_color, line);
	if (success)
		cub->elements_found++;
	return (success);
}