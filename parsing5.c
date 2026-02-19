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

int	is_cub(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(&path[len - 4], ".cub", 4) == 0);
}

t_config	pars_data(t_config config, char *argv)
{
	int		fd;
	char	*line;
	int		map_started;

	map_started = 0;
	if (!is_cub(argv))
		exit_error("error: map must be a .cub file !\n", &config);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit_error("cannot open the file", &config);
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, &config, &map_started, fd);
		free(line);
		if (map_started)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	if (map_started == 2)
		exit_error("content after map !\n", &config);
	check_config(&config);
	get_player(&config);
	return (config);
}

void	parse_color(char *line, int *color)
{
	int	i;
	int	k;

	i = 2;
	skip_spaces(line, &i);
	if (count_commas(line, i) != 2)
		return ;
	k = 0;
	while (k < 3)
	{
		if (k > 0 && (line[i++] != ',' || !line[i]))
			return ;
		skip_spaces(line, &i);
		if (!ft_isdigit(line[i]))
			return ;
		color[k] = ft_atoi(&line[i]);
		while (line[i] && ft_isdigit(line[i]))
			i++;
		skip_spaces(line, &i);
		k++;
	}
}