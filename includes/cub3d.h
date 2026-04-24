/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:10 by alejandj          #+#    #+#             */
/*   Updated: 2026/04/24 13:48:07 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>

# define WIDTH 800
# define HEIGHT 600

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_count;
}			t_map;

typedef struct s_cub
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	int		elements_found; // Tracks if we hit the magic number 6
	t_map	map;
	void	*mlx;
	void	*win;
}	t_cub;

// debug.c (Must erase at end)
void	print_cub_debug(t_cub *cub);

// file_parser.c
void	check_file_extension(const char *path);
void	parse_file(int fd, t_cub *cub);

// map_extraction.c
void	extract_map_line(char *line, t_cub *cub);
void	pad_map(t_cub *cub);

// map_validation.c
void	validate_cub_map(t_cub *cub);

// set_visuals.c
int		parse_element(char *line, t_cub *cub);

// window.c
int		create_window(t_cub *cub);
int		close_window(t_cub *cub);

// events.c
int		handle_key(int keycode, void *param);

// cub3d_utils.c
void	free_cub(t_cub *cub);
void	err_exit(t_cub *cub, char *message);

#endif