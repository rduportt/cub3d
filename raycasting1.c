/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:47:54 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:47:56 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_floor_raycast(t_data *data,
	t_raycasting *ray, t_coordinates *c)
{
	ray->cell_x = (int)ray->floor_x;
	ray->cell_y = (int)ray->floor_y;
	ray->tx = (int)(data->tex_width
			* (ray->floor_x - ray->cell_x)) & (data->tex_width - 1);
	ray->ty = (int)(data->tex_height
			* (ray->floor_y - ray->cell_y)) & (data->tex_height - 1);
	ray->floor_x += ray->floorstep_x;
	ray->floor_y += ray->floorstep_y;
	ray->color = create_rgb(data->config.color_floor[0],
			data->config.color_floor[1], data->config.color_floor[2]);
	data->buffer[c->y][c->x] = ray->color;
	ray->color = create_rgb(data->config.color_celling[0],
			data->config.color_celling[1], data->config.color_celling[2]);
	data->buffer[HAUTEUR - c->y - 1][c->x] = ray->color;
}

void	floor_raycast(t_data *data, t_raycasting *ray, t_coordinates *c)
{
	while (++c->y < HAUTEUR)
	{
		ray->raydir_x0 = data->player.dir_x - data->player.camera_plane_x;
		ray->raydir_y0 = data->player.dir_y - data->player.camera_plane_y;
		ray->raydir_x1 = data->player.dir_x + data->player.camera_plane_x;
		ray->raydir_y1 = data->player.dir_y + data->player.camera_plane_y;
		c->p = c->y - HAUTEUR / 2;
		ray->pos_z = 0.5 * HAUTEUR;
		ray->row_distance = ray->pos_z / c->p;
		ray->floorstep_x = ray->row_distance
			* (ray->raydir_x1 - ray->raydir_x0) / LONGUEUR;
		ray->floorstep_y = ray->row_distance
			* (ray->raydir_y1 - ray->raydir_y0) / LONGUEUR;
		ray->floor_x = data->player.pos_x + ray->row_distance * ray->raydir_x0;
		ray->floor_y = data->player.pos_y + ray->row_distance * ray->raydir_y0;
		c->x = -1;
		while (++c->x < LONGUEUR)
			horizontal_floor_raycast(data, ray, c);
	}
}

void	val_init(t_data *data, t_raycasting *ray, t_coordinates c)
{
	data->player.camera_x = 2 * c.x / (double)LONGUEUR - 1;
	ray->raydir_x = data->player.dir_x
		+ data->player.camera_plane_x * data->player.camera_x;
	ray->raydir_y = data->player.dir_y
		+ data->player.camera_plane_y * data->player.camera_x;
	ray->map_x = (int) data->player.pos_x;
	ray->map_y = (int) data->player.pos_y;
	if (ray->raydir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
}
