/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:50:52 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/05 20:21:36 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_colision(t_cub *cub, double next_x, double next_y)
{
	if (cub->map.grid[(int)cub->player.y][(int)next_x] != '1')
		cub->player.x = next_x;
	if (cub->map.grid[(int)next_y][(int)cub->player.x] != '1')
		cub->player.y = next_y;
}

int	move_player(t_cub *cub)
{
	double	next_x;
	double	next_y;

	if (cub->keys.w)
		return (
			next_x = cub->player.x + cub->player.dir_x * MOVE_SPEED,
			next_y = cub->player.y + cub->player.dir_y * MOVE_SPEED,
			handle_colision(cub, next_x, next_y), 1);
	if (cub->keys.a)
		return (
			next_x = cub->player.x - cub->player.plane_x * MOVE_SPEED,
			next_y = cub->player.y - cub->player.plane_y * MOVE_SPEED,
			handle_colision(cub, next_x, next_y), 1);
	if (cub->keys.s)
		return (
			next_x = cub->player.x - cub->player.dir_x * MOVE_SPEED,
			next_y = cub->player.y - cub->player.dir_y * MOVE_SPEED,
			handle_colision(cub, next_x, next_y), 1);
	if (cub->keys.d)
		return (
			next_x = cub->player.x + cub->player.plane_x * MOVE_SPEED,
			next_y = cub->player.y + cub->player.plane_y * MOVE_SPEED,
			handle_colision(cub, next_x, next_y), 1);
	return (0);
}

static void	rotate_player(t_player *player, double speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(speed) - player->dir_y * sin(speed);
	player->dir_y = old_dir_x * sin(speed) + player->dir_y * cos(speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(speed)
		- player->plane_y * sin(speed);
	player->plane_y = old_plane_x * sin(speed) + player->plane_y * cos(speed);
}

int	move_chamera(t_cub *cub)
{
	if (cub->keys.left)
		return (rotate_player(&cub->player, -ROT_SPEED), 1);
	if (cub->keys.right)
		return (rotate_player(&cub->player, ROT_SPEED), 1);
	return (0);
}
