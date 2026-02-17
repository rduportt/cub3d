/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:48:23 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:48:24 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_vertical_wall(t_data *data,
	t_raycasting *ray, t_camera *cam, t_coordinates *c)
{
	if (ray->side == 1 && ray->raydir_y < 0)
		ray->tex_x = data->tex_width - ray->tex_x - 1;
	ray->step = 1.0 * data->tex_height / cam->line_height;
	ray->tex_pos = (cam->draw_start - HAUTEUR
			/ 2 + cam->line_height / 2) * ray->step;
	c->y = cam->draw_start;
	while (++c->y < cam->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (data->tex_height - 1);
		ray->tex_pos += ray->step;
		ray->color = data->textures[ray->tex_num][data->tex_width
			* ray->tex_y + ray->tex_x];
		data->buffer[c->y][c->x] = ray->color;
	}
}

void	texture_display(t_data *data,
	t_raycasting *ray, t_camera *cam, t_coordinates *c)
{
	if (ray->side == 1)
	{
		if (ray->raydir_y > 0)
			ray->orientation = 0;
		else
			ray->orientation = 1;
	}
	else
	{
		if (ray->raydir_x > 0)
			ray->orientation = 2;
		else
			ray->orientation = 3;
	}
	ray->tex_num = ((data->config.map[ray->map_y][ray->map_x]
				- '0') - 1) + ray->orientation;
	if (ray->side == 0)
		ray->wall_x = data->player.pos_y + ray->perp_wall_dist * ray->raydir_y;
	else
		ray->wall_x = data->player.pos_x + ray->perp_wall_dist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)data->tex_width);
	if (ray->side == 0 && ray->raydir_x > 0)
		ray->tex_x = data->tex_width - ray->tex_x - 1;
	texture_vertical_wall(data, ray, cam, c);
}

void	untextured_display(t_data *data,
	t_raycasting *ray, t_camera *cam, t_coordinates *c)
{
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + HAUTEUR / 2;
	if (cam->draw_end >= HAUTEUR)
		cam->draw_end = HAUTEUR - 1;
	if (data->config.map[ray->map_y][ray->map_x] == '1')
		cam->color = 0xFF0000;
	else
		cam->color = 0xFFFF00;
	if (ray->side == 1)
		cam->color = ((cam->color >> 1) & 0x7F7F7F);
	c->draw_start = cam->draw_start;
	c->draw_end = cam->draw_end;
	draw_ver_line(&data->img, *c, cam->color);
}

void	raycasting(t_data *data)
{
	t_raycasting	ray;
	t_camera		cam;
	t_coordinates	c;

	clear_screen(&data->img);
	c.x = -1;
	c.y = -1;
	if (data->texture == 1)
		floor_raycast(data, &ray, &c);
	c.x = -1;
	while (++c.x < LONGUEUR)
	{
		val_init(data, &ray, c);
		dda(data, &ray);
		wall_height(&cam, &ray);
		if (data->texture == 1)
			texture_display(data, &ray, &cam, &c);
		else
			untextured_display(data, &ray, &cam, &c);
	}
	if (data->texture == 1)
		draw_buffer(data);
	data->player.move_speed = 0.1;
	data->player.rot_speed = 0.06;
	mlx_put_image_to_window(data->img.mlx, data->img.win, data->img.img, 0, 0);
}
