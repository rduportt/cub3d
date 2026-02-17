/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2026/02/13 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

void	free_config(t_config *config)
{
	int	i;

	i = 0;
	if (config->map)
	{
		while (config->map[i])
			free(config->map[i++]);
		free(config->map);
	}
	if (config->we_texture)
		free(config->we_texture);
	if (config->ww_texture)
		free(config->ww_texture);
	if (config->wn_texutre)
		free(config->wn_texutre);
	if (config->ws_texure)
		free(config->ws_texure);
}

void	exit_error(char *msg, t_config *config)
{
	err(msg);
	free_config(config);
	exit(1);
}

void	get_player(t_config *config)
{
	int	i;
	int	j;

	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == 'N' || config->map[i][j] == 'E'
				|| config->map[i][j] == 'S'
				|| config->map[i][j] == 'W')
			{
				config->player_i = i;
				config->player_j = j;
				config->player_direction = config->map[i][j];
			}
			j++;
		}
		i++;
	}
}

void	init_config(t_config *config)
{
	config->color_celling[0] = -1;
	config->color_celling[1] = -1;
	config->color_celling[2] = -1;
	config->color_floor[0] = -1;
	config->color_floor[1] = -1;
	config->color_floor[2] = -1;
	config->height = -1;
	config->player_i = -1;
	config->player_j = -1;
	config->map = NULL;
	config->we_texture = NULL;
	config->wn_texutre = NULL;
	config->ws_texure = NULL;
	config->ww_texture = NULL;
}
