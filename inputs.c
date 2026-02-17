/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:47:32 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:47:34 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_img *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit(0);
}

void	key_w(t_data *data)
{
	if (data->config.map[(int)data->player.pos_y][(int)(data->player.pos_x
		+ data->player.dir_x * data->player.move_speed)] == '0')
		data->player.pos_x += data->player.dir_x * data->player.move_speed;
	if (data->config.map[(int)(data->player.pos_y + data->player.dir_y
			* data->player.move_speed)][(int)data->player.pos_x] == '0')
		data->player.pos_y += data->player.dir_y * data->player.move_speed;
}

void	key_s(t_data *data)
{
	if (data->config.map[(int)data->player.pos_y][(int)(data->player.pos_x
		- data->player.dir_x * data->player.move_speed)] == '0')
		data->player.pos_x -= data->player.dir_x * data->player.move_speed;
	if (data->config.map[(int)(data->player.pos_y - data->player.dir_y
			* data->player.move_speed)][(int)data->player.pos_x] == '0')
		data->player.pos_y -= data->player.dir_y * data->player.move_speed;
}

void	key_a(t_data *data)
{
	if (data->config.map[(int)data->player.pos_y][(int)(data->player.pos_x
		+ (-data->player.dir_y * data->player.move_speed))] == '0')
		data->player.pos_x = data->player.pos_x
			+ (-data->player.dir_y * data->player.move_speed);
	if (data->config.map[(int)(data->player.pos_y + data->player.dir_x
			* data->player.move_speed)][(int)data->player.pos_x] == '0')
		data->player.pos_y = data->player.pos_y
			+ data->player.dir_x * data->player.move_speed;
}

void	key_d(t_data *data)
{
	if (data->config.map[(int)data->player.pos_y][(int)(data->player.pos_x
		+ data->player.dir_y * data->player.move_speed)] == '0')
		data->player.pos_x = data->player.pos_x
			+ data->player.dir_y * data->player.move_speed;
	if (data->config.map[(int)(data->player.pos_y - data->player.dir_x
			* data->player.move_speed)][(int)data->player.pos_x] == '0')
		data->player.pos_y = data->player.pos_y
			- data->player.dir_x * data->player.move_speed;
}
