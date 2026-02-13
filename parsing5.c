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

void	parse_line(char *line, t_config *config)
{
	if (ft_strlen(line) <= 1)
		return ;
	if (ft_strncmp (line, "NO ", 3) == 0)
		config->wn_texutre = parse_texture(line);
	if (ft_strncmp (line, "SO ", 3) == 0)
		config->ws_texure = parse_texture(line);
	if (ft_strncmp (line, "WE ", 3) == 0)
		config->ww_texture = parse_texture(line);
	if (ft_strncmp (line, "EA ", 3) == 0)
		config->we_texture = parse_texture(line);
	if (ft_strncmp (line, "F ", 2) == 0)
		parse_color(line, config->color_floor);
	if (ft_strncmp (line, "C ", 2) == 0)
		parse_color(line, config->color_celling);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) <= 1)
		return (0);
	while (line[i])
	{
		if ((line[i] == '0' || line[i] == '1'
				|| line[i] == ' ' || line[i] == 'N'
				|| line[i] == 'E' || line[i] == 'S' || line[i] == 'W'))
		{
			i++;
			continue ;
		}
		else if (line[i] == '\n')
			break ;
		else
			return (0);
	}
	return (1);
}
