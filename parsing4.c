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

int	is_xpm(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(&path[len - 4], ".xpm", 4) == 0);
}

void	check_config(t_config *config)
{
	if (!config->ws_texure || !config->ww_texture
		|| !config->we_texture || !config->wn_texutre)
		exit_error("error: missing texture !\n", config);
	if (!is_xpm(config->ws_texure) || !is_xpm(config->ww_texture)
		|| !is_xpm(config->we_texture) || !is_xpm(config->wn_texutre))
		exit_error("error: invalid texture format, must be .xpm !\n", config);
	if (config->color_celling[0] == -1
		|| config->color_celling[1] == -1
		|| config->color_celling[2] == -1
		|| config->color_floor[0] == -1
		|| config->color_floor[1] == -1
		|| config->color_floor[2] == -1)
		exit_error("error: missing colors !\n", config);
	check_colors(config);
	if (!config->map)
		exit_error("error: no map structur !\n", config);
	check_map(config->map, config);
}

char	*parse_texture(char *line)
{
	char	*tx;
	int		i;

	i = 3;
	while (line[i] == ' ')
		i++;
	tx = ft_strdup(&line[i]);
	tx[ft_strlen(tx) - 1] = '\0';
	return (tx);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

int	count_commas(char *line, int start)
{
	int	count;
	int	j;

	count = 0;
	j = start;
	while (line[j] && line[j] != '\n')
	{
		if (line[j] == ',')
			count++;
		j++;
	}
	return (count);
}
