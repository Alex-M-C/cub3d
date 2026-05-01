/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:24:57 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/01 22:55:21 by alejandj         ###   ########.fr       */
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

static int	move_player(t_cub *cub)
{
	if (cub->keys.w)
		return (
			cub->player.x += cub->player.dir_x * MOVE_SPEED,
			cub->player.y += cub->player.dir_y * MOVE_SPEED, 1
		);
	if (cub->keys.a)
		return (
			cub->player.x -= cub->player.plane_x * MOVE_SPEED,
			cub->player.y -= cub->player.plane_y * MOVE_SPEED, 1
		);
	if (cub->keys.s)
		return (
			cub->player.x -= cub->player.dir_x * MOVE_SPEED,
			cub->player.y -= cub->player.dir_y * MOVE_SPEED, 1
		);
	if (cub->keys.d)
		return (
			cub->player.x += cub->player.plane_x * MOVE_SPEED,
			cub->player.y += cub->player.plane_y * MOVE_SPEED, 1
		);
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
	if (move_player(cub) || move_chamera(cub))
	{
		mlx_clear_window(cub->mlx, cub->win);
		draw_2d_map(cub);
		raycast_loop(cub);
	}
	return (0);
}
