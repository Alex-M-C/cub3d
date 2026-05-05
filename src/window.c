/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:10:52 by alejandj          #+#    #+#             */
/*   Updated: 2026/05/05 18:48:50 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	create_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (1);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "Cub3d");
	if (!cub->win)
		return (1);
	return (0);
}

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	free_cub(cub);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
}
