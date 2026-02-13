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

int	get_height_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	check_map(char **map, t_config *config)
{
	char	**map_copy;
	int		i;

	i = 0;
	player_in_map(map, config);
	get_player(config);
	config->height = get_height_map(map);
	map_copy = malloc(sizeof(char *) * (config->height + 1));
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		i++;
	}
	map_copy[i] = NULL;
	flood_fill(config->player_i, config->player_j, map_copy, config);
	i = 0;
	while (map_copy[i])
		free(map_copy[i++]);
	free(map_copy);
}

void	free_map_copy(char **map_copy)
{
	int	i;

	i = 0;
	while (map_copy[i])
		free(map_copy[i++]);
	free(map_copy);
}

void	flood_fill(int i, int j, char **map_copy, t_config *config)
{
	if (i < 0 || i >= config->height || j < 0
		|| !map_copy[i][j] || map_copy[i][j] == '\n' || map_copy[i][j] == ' ')
	{
		free_map_copy(map_copy);
		exit_error("error: map not closed !\n", config);
	}
	if (map_copy[i][j] == '1' || map_copy[i][j] == 'X')
		return ;
	map_copy[i][j] = 'X';
	flood_fill(i + 1, j, map_copy, config);
	flood_fill(i, j + 1, map_copy, config);
	flood_fill(i - 1, j, map_copy, config);
	flood_fill(i, j - 1, map_copy, config);
}

void	check_colors(t_config *config)
{
	if (config->color_floor[0] < 0
		|| config->color_floor[0] > 255
		|| config->color_floor[1] < 0
		|| config->color_floor[1] > 255
		|| config->color_floor[2] < 0
		|| config->color_floor[2] > 255
		|| config->color_celling[0] < 0
		|| config->color_celling[0] > 255
		|| config->color_celling[1] < 0
		|| config->color_celling[1] > 255
		|| config->color_celling[2] < 0
		|| config->color_celling[2] > 255)
		exit_error("error: bad RGB values\n", config);
}
