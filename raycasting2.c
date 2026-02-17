/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:48:02 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:48:15 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_player(t_data *data, t_raycasting *ray)
{
	if (data->config.map[ray->map_y][ray->map_x] == 'N' ||
		data->config.map[ray->map_y][ray->map_x] == 'S' ||
		data->config.map[ray->map_y][ray->map_x] == 'E' ||
		data->config.map[ray->map_y][ray->map_x] == 'W')
		data->config.map[ray->map_y][ray->map_x] = '0';
}

void	check_wall(t_data *data, t_raycasting *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0
				- data->player.pos_x) * ray->delta_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0
				- data->player.pos_y) * ray->delta_dist_y;
	}
}

void	hit_wall(t_data *data, t_raycasting *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->config.map[ray->map_y][ray->map_x] != '0')
			ray->hit = 1;
	}
}

void	dda(t_data *data, t_raycasting *ray)
{
	check_wall(data, ray);
	is_player(data, ray);
	hit_wall(data, ray);
}

void	wall_height(t_camera *cam, t_raycasting *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	cam->line_height = (int)(HAUTEUR / ray->perp_wall_dist);
	cam->draw_start = -cam->line_height / 2 + HAUTEUR / 2;
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + HAUTEUR / 2;
	if (cam->draw_end >= HAUTEUR)
		cam->draw_end = HAUTEUR - 1;
}
