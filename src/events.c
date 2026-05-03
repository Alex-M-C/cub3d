/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:24:57 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/02 20:54:49 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_key_press(int keycode, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keycode == ESC)
		close_window(cub);
	if (keycode == KEY_W)
		cub->keys.w = 1;
	else if (keycode == KEY_A)
		cub->keys.a = 1;
	else if (keycode == KEY_S)
		cub->keys.s = 1;
	else if (keycode == KEY_D)
		cub->keys.d = 1;
	else if (keycode == LEFT_KEY)
		cub->keys.left = 1;
	else if (keycode == RIGHT_KEY)
		cub->keys.right = 1;
	return (0);
}

int	handle_key_release(int keycode, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keycode == KEY_W)
		cub->keys.w = 0;
	else if (keycode == KEY_A)
		cub->keys.a = 0;
	else if (keycode == KEY_S)
		cub->keys.s = 0;
	else if (keycode == KEY_D)
		cub->keys.d = 0;
	else if (keycode == LEFT_KEY)
		cub->keys.left = 0;
	else if (keycode == RIGHT_KEY)
		cub->keys.right = 0;
	return (0);
}

static void	handle_colision(t_cub *cub, double next_x, double next_y)
{
	if (cub->map.grid[(int)cub->player.y][(int)next_x] != '1')
		cub->player.x = next_x;
	if (cub->map.grid[(int)next_y][(int)cub->player.x] != '1')
		cub->player.y = next_y;
}

static int	move_player(t_cub *cub)
{
	double next_x;
	double next_y;

	next_x = 0;
	next_y = 0;
	if (cub->keys.w)
	{
		next_x = cub->player.x + cub->player.dir_x * MOVE_SPEED;
		next_y = cub->player.y + cub->player.dir_y * MOVE_SPEED;
		handle_colision(cub, next_x, next_y);
		return (1);
	}
	if (cub->keys.a)
	{
		next_x = cub->player.x - cub->player.plane_x * MOVE_SPEED;
		next_y = cub->player.y - cub->player.plane_y * MOVE_SPEED;
		handle_colision(cub, next_x, next_y);
		return (1);
	}
	if (cub->keys.s)
	{
		next_x = cub->player.x - cub->player.dir_x * MOVE_SPEED;
		next_y = cub->player.y - cub->player.dir_y * MOVE_SPEED;
		handle_colision(cub, next_x, next_y);
		return (1);
	}
	if (cub->keys.d)
	{
		next_x = cub->player.x + cub->player.plane_x * MOVE_SPEED;
		next_y = cub->player.y + cub->player.plane_y * MOVE_SPEED;
		handle_colision(cub, next_x, next_y);
		return (1);
	}
	return (0);
}

static int	move_chamera(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = 0;
	old_plane_x = 0;
	if (cub->keys.left)
	{
		old_dir_x = cub->player.dir_x;
		cub->player.dir_x = cub->player.dir_x * cos(-ROT_SPEED) - cub->player.dir_y * sin(-ROT_SPEED);
		cub->player.dir_y = old_dir_x * sin(-ROT_SPEED) + cub->player.dir_y * cos(-ROT_SPEED);
		old_plane_x = cub->player.plane_x;
		cub->player.plane_x = cub->player.plane_x * cos(-ROT_SPEED) - cub->player.plane_y * sin(-ROT_SPEED);
		cub->player.plane_y = old_plane_x * sin (-ROT_SPEED) + cub->player.plane_y * cos(-ROT_SPEED);
		return (1);
	}
	if (cub->keys.right)
	{
		old_dir_x = cub->player.dir_x;
		cub->player.dir_x = cub->player.dir_x * cos(ROT_SPEED) - cub->player.dir_y * sin(ROT_SPEED);
		cub->player.dir_y = old_dir_x * sin(ROT_SPEED) + cub->player.dir_y * cos(ROT_SPEED);
		old_plane_x = cub->player.plane_x;
		cub->player.plane_x = cub->player.plane_x * cos(ROT_SPEED) - cub->player.plane_y * sin(ROT_SPEED);
		cub->player.plane_y = old_plane_x * sin (ROT_SPEED) + cub->player.plane_y * cos(ROT_SPEED);
		return (1);
	}
	return (0);
}

int	handle_move(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (move_player(cub))
	{
		//mlx_clear_window(cub->mlx, cub->win);
		//draw_2d_map(cub);
		raycast_loop(cub);
	}
	if (move_chamera(cub))
	{
		//mlx_clear_window(cub->mlx, cub->win);
		//draw_2d_map(cub);
		raycast_loop(cub);
	}
	return (0);
}
