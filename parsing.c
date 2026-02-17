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

void	player_in_map(char **map, t_config *config)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'S' || map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		exit_error("error: no player or too manyplayers on the map !\n",
			config);
}

void	handle_map_line(char ***map, int *i, int *map_size, char *line)
{
	if (*i >= *map_size)
	{
		*map_size *= 2;
		*map = realloc(*map, sizeof(char *) * (*map_size));
	}
	(*map)[(*i)++] = ft_strdup(line);
}

char	**parse_map(char *first_line, int fd, t_config *config)
{
	int		i;
	char	**map;
	char	*line;
	int		map_size;

	i = 0;
	map_size = 100;
	map = malloc(sizeof(char *) * map_size);
	map[i++] = ft_strdup(first_line);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strlen(line) > 1 && is_map_line(line))
			handle_map_line(&map, &i, &map_size, line);
		else if (ft_strlen(line) > 1)
		{
			free(line);
			exit_error("error: invalid content after map !\n", config);
		}
		free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

void	process_line(char *line, t_config *config, int *map_started, int fd)
{
	if (is_map_line(line))
	{
		*map_started = 1;
		config->map = parse_map(line, fd, config);
	}
	else if (*map_started == 0)
		parse_line(line, config);
}

t_config	pars_data(t_config config, char *argv)
{
	int		fd;
	char	*line;
	int		map_started;

	map_started = 0;
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
	check_config(&config);
	get_player(&config);
	return (config);
}
