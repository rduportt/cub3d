/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:47:07 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:47:11 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_buffer(t_data *data)
{
	int				y;
	unsigned int	*dst;

	dst = (unsigned int *)data->img.img_str;
	y = 0;
	while (y < HAUTEUR)
	{
		memcpy(dst + (y * LONGUEUR),
			data->buffer[y],
			LONGUEUR * sizeof(unsigned int));
		y++;
	}
}

void	clear_screen(t_img *img)
{
	int				total_pixels;
	unsigned int	*pixel;
	int				i;

	total_pixels = LONGUEUR * HAUTEUR;
	pixel = (unsigned int *)img->img_str;
	i = 0;
	while (i < total_pixels)
	{
		pixel[i] = 0x000000;
		i++;
	}
}

void	draw_ver_line(t_img *img, t_coordinates c, int color)
{
	int				y;
	unsigned int	*pixel;

	if (c.draw_start < 0)
		c.draw_start = 0;
	if (c.draw_end >= HAUTEUR)
		c.draw_end = HAUTEUR - 1;
	y = c.draw_start;
	while (y <= c.draw_end)
	{
		pixel = (unsigned int *)(img->img_str
				+ (y * img->size_line)
				+ (c.x * (img->bits / 8)));
		*pixel = color;
		y++;
	}
}
