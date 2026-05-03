/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 20:50:36 by alejandj          #+#    #+#             */
/*   Updated: 2026/04/28 17:48:51 by alejandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_ray(t_ray *ray, t_cub *cub, int px)
{
	ray->camera_x = 2 * px / (double)WIDTH - 1;

	ray->ray_dir_x = cub->player.dir_x + (cub->player.plane_x * ray->camera_x);
	ray->ray_dir_y = cub->player.dir_y + (cub->player.plane_y * ray->camera_x);

	ray->map_x = (int)cub->player.x;
	ray->map_y = (int)cub->player.y;

	// Cuidado division entre 0
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);

	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->player.x) * ray->delta_dist_x;
	}

	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->player.y) * ray->delta_dist_y;
	}

	ray->real_dist = 0;
}

void	raycast_loop(t_cub *cub)
{
	t_ray	ray;
	int		i;
	int		hit;

	i = -1;
	while (++i < WIDTH)
	{
		// 1. INIT RAY
		init_ray(&ray, cub, i);
		
		// 2. EJECUTAR DDA (El bucle de saltos)
		// -> Aquí es donde el rayo "camina" hasta chocar.
		hit = 0;
		while (!hit)
		{
			if (ray.side_dist_x < ray.side_dist_y)
			{
				ray.side_dist_x += ray.delta_dist_x;
				ray.map_x += ray.step_x;
				ray.side = 0;	
			}
			else
			{
				ray.side_dist_y += ray.delta_dist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			if (cub->map.grid[ray.map_y][ray.map_x] == '1')
				hit = 1;
		}
		
		// 3. CALCULAR DISTANCIA AL MURO
		// -> Aquí mides cuánto ha recorrido el rayo.
		if (ray.side == 0)
			ray.real_dist = ray.side_dist_x - ray.delta_dist_x;
		else
			ray.real_dist = ray.side_dist_y - ray.delta_dist_y;

		ray.hit_x = cub->player.x + (ray.ray_dir_x * ray.real_dist);
		ray.hit_y = cub->player.y + (ray.ray_dir_y * ray.real_dist);

		//draw_ray(cub, &ray, 0xFF0000);
		draw_vertical_line(cub, &ray, i);

		// 4. CALCULAR ALTURA DE LÍNEA Y DIBUJAR
		// -> Aquí decides qué tan grande se ve el muro en el píxel 'i'.
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img_ptr, 0, 0);
}