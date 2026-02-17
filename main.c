/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:47:43 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:47:44 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_data *data)
{
	raycasting(data);
	return (0);
}

void	init_buffer(t_data *data)
{
	int	i;
	int	j;

	data->buffer = malloc(sizeof(uint32_t *) * HAUTEUR);
	i = 0;
	while (i < HAUTEUR)
	{
		data->buffer[i] = malloc(sizeof(uint32_t) * LONGUEUR);
		j = 0;
		while (j < LONGUEUR)
		{
			data->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	init_data(t_data *data, t_config config, char *texture_files[4])
{
	int	i;

	i = 0;
	data->texture = 1;
	data->player.pos_x = config.player_j;
	data->player.pos_y = config.player_i;
	init_player_direction(data, config);
	init_camera_plane(data, config);
	data->player.move_speed = 0.15;
	data->player.rot_speed = 0.05;
	while (++i < 4)
	{
		data->textures[i] = NULL;
		data->tex_img[i] = NULL;
	}
	init_buffer(data);
	texture_files[0] = config.ws_texure;
	texture_files[1] = config.wn_texutre;
	texture_files[2] = config.ww_texture;
	texture_files[3] = config.we_texture;
}

int	init_data_image(t_data *data, char *texture_files[4])
{
	int	i;

	i = -1;
	data->img.win = mlx_new_window
		(data->img.mlx, LONGUEUR, HAUTEUR, "Cube3D");
	data->img.img = mlx_new_image(data->img.mlx, LONGUEUR, HAUTEUR);
	data->img.img_str = mlx_get_data_addr(data->img.img,
			&data->img.bits, &data->img.size_line, &data->img.endian);
	while (++i < 4)
	{
		data->tex_img[i] = mlx_xpm_file_to_image(data->img.mlx,
				texture_files[i], &data->tex_height, &data->tex_width);
		if (!data->tex_img[i])
			return (free_data(data, i));
		data->textures[i] = (uint32_t *)mlx_get_data_addr(data->tex_img[i],
				&data->tex_bits[i], &data->tex_size_line[i],
				&data->tex_endian[i]);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_config		config;
	char			*texture_files[4];

	(void) argc;
	init_config(&config);
	config = pars_data(config, argv[1]);
	init_data(&data, config, texture_files);
	data.config = config;
	data.img.mlx = mlx_init();
	if (!data.img.mlx)
		return (-1);
	if (init_data_image(&data, texture_files) == -1)
		return (printf("error loading image\n"));
	raycasting(&data);
	mlx_hook(data.img.win, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.img.win, DestroyNotify,
		StructureNotifyMask, close_window, &data);
	mlx_loop_hook(data.img.mlx, game_loop, &data);
	mlx_loop(data.img.mlx);
}
