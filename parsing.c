#include "cub3d.h"

int	err(char *str)
{
	while (*str)
		write(2, ++str, 1);
	return (1);
}

void	init_config(t_config *config)
{
	config->color_celling = -1;
	config->color_floor = -1;
	config->map = NULL;
	config->we_texture = NULL;
	config->wn_texutre = NULL;
	config->ws_texure = NULL;
	config->ww_texture = NULL;
	config->map_lenght = -1;
	config->map_width = -1;
}

void	parse_line()
{

}

int	is_map_line(char *line, int has_a_player)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if ((line[i] < '0' && line[i] > '9' || line[i] == ' '))
		{
			i++;
			continue;
		}
		else if (line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W')
		{
			i++;
			has_a_player++;
		}
		else
			return (0);
	}
	return (1);
}

char	**parse_map(char *first_line, int fd)
{
	int		i;
	char **map;
	char *line;
	int	has_a_player;
	int	map_size;

	has_a_player = 0;
	i = 0;
	map_size = 100;
	map = malloc(sizeof(char*) * map_size);

	map[i++] = ft_strdup(first_line);
	while(line = get_next_line(fd))
	{
		if (ft_strlen(line) <= 1)
		{
			free(line);
			break;
		}
		if (is_map_line(line, &has_a_player))
		{
			if (i >= map_size)
			{
				map_size * 2;
				map = realloc(map, sizeof(char*) * map_size);
			}
			map[i++] = ft_strdup(line);
		}
		else
		{
			return(err("wrong map format try again !"));
			exit(0);
		}
		free(line);
	}
	if (has_a_player == 0 || has_a_player > 1)
	{
		return (err("only one player is allowed"));
		exit(0);
	}
	map[i] == NULL;
	return (map);
}

t_config	pars_data(t_config config)
{
	int		fd;
	char	*line;
	int		map_started;

	map_started = 0;
	fd = open("cube3d.cub", O_RDONLY);
	if (fd < 0)
	{
		err("cannot open the file");
		exit(0);
	}
	while (line = get_next_line(fd))
	{
		if (is_map_line(line))
		{
			map_started = 1;
			config.map = parse_map(line, fd);
			free(line);
			break;
		}
		parse_line(line, &config, &map_started);
	}
}
