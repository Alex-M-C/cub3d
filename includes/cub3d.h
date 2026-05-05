/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 13:53:10 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/05 19:53:54 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define TILE_SIZE 16
# define TEX_HEIGHT 64
# define TEX_WIDTH 64
# define NO 0
# define SO 1
# define EA 2
# define WE 3

# define MOVE_SPEED 0.03
# define ROT_SPEED 0.009

# define ESC 65307

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define LEFT_KEY 65361 
# define RIGHT_KEY 65363


typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_count;
}			t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_draw
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
}	t_draw;

typedef struct s_img
{
	void	*img_ptr;       // The pointer to the loaded image
	char	*addr;          // The raw memory address of the pixels
	int		width;          // Texture width (e.g., 64)
	int		height;         // Texture height (e.g., 64)
	int		bpp;            // Bits per pixel
	int		line_length;    // How many bytes are in a single row of the image
	int		endian;
}   t_img;

// Ray info
typedef struct s_ray
{
	double	camera_x;		// Escala que determina la inclinacion de cada rayo (Izq: -1, Centro: 0, Derecha: 1)
	double	ray_dir_x;		// Direccion del rayo (eje X)
	double	ray_dir_y;		// Direccion del rayo (eje Y)
	
	int	map_x;				// Posicion X del rayo en el mapa
	int	map_y;				// Posicion X del rayo en el mapa
	
	double	delta_dist_x;	// Distancia que recorre el rayo para avanzar 1 unidad (eje X)
	double	delta_dist_y;	// Distancia que recorre el rayo para avanzar 1 unidad (eje Y)
	
	double	side_dist_x;	// Distancia que hay desde pj hasta donde esta ahora mismo el rayo (eje X)
	double	side_dist_y;	// Distancia que hay desde pj hasta donde esta ahora mismo el rayo (eje Y)

	int		step_x;			// Hacia donde va el rayo (Izq: -1, Der: 1, Arriba: -1, Abajo: 1)
	int		step_y;

	int		side;			// Indica con que cara de la pared se ha chocado (cara: norte/sur, cara: este/oeste)

	double	real_dist;		// Distancia real

	double	hit_x;			// Punto donde choca con la pared
	double	hit_y;
}			t_ray;

// Elements to draw ray
typedef struct s_line
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;
	double	dx;
	double	dy;
	double	steps;
	double	current_x;
	double	current_y;
	double	move_x;
	double	move_y;
}			t_line;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}			t_keys;

typedef struct s_cub
{
	t_img		screen;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_color;
	int			ceiling_color;
	int			elements_found; // Tracks if we hit the magic number 6
	t_map		map;
	t_player	player;
	t_img		textures[4]; // 0: North, 1: South, 2: East, 3: West
	void		*mlx;
	void		*win;
	t_keys		keys;
}				t_cub;

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
int		handle_key_press(int keycode, void *param);
int		handle_key_release(int keycode, void *param);
int		handle_move(void *param);

// player_move.c
int		move_player(t_cub *cub);
int		move_chamera(t_cub *cub);

// raycast.c
void	raycast_loop(t_cub *cub);

// render.c
void	draw_ray(t_cub *cub, t_ray *ray, int color);
void	draw_2d_map(t_cub *cub);

// render3d.c
void	draw_vertical_line(t_cub *cub, t_ray *ray, int x);

// cub3d_utils.c
void	free_cub(t_cub *cub);
void	err_exit(t_cub *cub, char *message);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif