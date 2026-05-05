/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:24:57 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/05 19:57:48 by alejandj         ###   ########.fr       */
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

int	handle_move(void *param)
{
	t_cub	*cub;
	int		moved;

	cub = (t_cub *)param;
	moved = 0;
	if (move_player(cub))
		moved = 1;
	if (move_chamera(cub))
		moved = 1;
	if (moved)
		raycast_loop(cub);
	return (0);
}
