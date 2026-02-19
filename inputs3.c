/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:47:32 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:47:34 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode < 256)
		data->key_tab[keycode] = 0;
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 113)
	{
		data->texture++;
		data->texture %= 2;
	}
	else if (keycode == ESC_KEY)
		close_window(data);
	else if (keycode < 256)
		data->key_tab[keycode] = 1;
	else if (keycode == KEY_LEFT)
		key_left(data);
	else if (keycode == KEY_RIGHT)
		key_right(data);
	return (0);
}
