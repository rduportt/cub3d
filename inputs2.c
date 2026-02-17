/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:47:39 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:47:40 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_direction(t_data *data, t_config config)
{
	if (config.player_direction == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
	}
	else if (config.player_direction == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
	}
	else if (config.player_direction == 'E')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
	}
	else
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
	}
}

void	key_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-data->player.rot_speed)
		- data->player.dir_y * sin(-data->player.rot_speed);
	data->player.dir_y = old_dir_x * sin(-data->player.rot_speed)
		+ data->player.dir_y * cos(-data->player.rot_speed);
	old_plane_x = data->player.camera_plane_x;
	data->player.camera_plane_x = data->player.camera_plane_x
		* cos(-data->player.rot_speed) - data->player.camera_plane_y
		* sin(-data->player.rot_speed);
	data->player.camera_plane_y = old_plane_x * sin(-data->player.rot_speed)
		+ data->player.camera_plane_y * cos(-data->player.rot_speed);
}

void	key_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(data->player.rot_speed)
		- data->player.dir_y * sin(data->player.rot_speed);
	data->player.dir_y = old_dir_x * sin(data->player.rot_speed)
		+ data->player.dir_y * cos(data->player.rot_speed);
	old_plane_x = data->player.camera_plane_x;
	data->player.camera_plane_x = data->player.camera_plane_x
		* cos(data->player.rot_speed) - data->player.camera_plane_y
		* sin(data->player.rot_speed);
	data->player.camera_plane_y = old_plane_x * sin(data->player.rot_speed)
		+ data->player.camera_plane_y * cos(data->player.rot_speed);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 113)
	{
		data->texture++;
		data->texture %= 2;
	}
	if (keycode == ESC_KEY)
		close_window(data);
	if (keycode == KEY_W)
		key_w(data);
	if (keycode == KEY_S)
		key_s(data);
	if (keycode == KEY_A)
		key_a(data);
	if (keycode == KEY_D)
		key_d(data);
	if (keycode == KEY_RIGHT)
		key_right(data);
	if (keycode == KEY_LEFT)
		key_left(data);
	return (0);
}
