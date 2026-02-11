#include "cub3d.h"

int	err(char *str)
{
	while (*str)
		write(2, ++str, 1);
	return (1);
}

void	init_config(t_config *config)
{
	config->color_celling[0] = -1;
	config->color_celling[1] = -1;
	config->color_celling[2] = -1;
	config->color_floor[0] = -1;
	config->color_floor[1] = -1;
	config->color_floor[2] = -1;
	config->map = NULL;
	config->we_texture = NULL;
	config->wn_texutre = NULL;
	config->ws_texure = NULL;
	config->ww_texture = NULL;
}

int	get_height_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	check_map(char **map)
{
	int	i;
	int	j;
	int	player_i;
	int	player_j;
	int	height;
	char	**map_copy;

	height = get_height_map(map);
	map_copy = malloc(sizeof(char*) * height + 1);
	i = 0;
	player_in_map(map);
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		i++;
	}

	flood_fill(player_i, player_j);
}

void	check_config(t_config *config)
{
	int	i;
	int	j;

	player_in_map(config->map);
	if (!config->ws_texure || !config->ww_texture || !config->we_texture || !config->wn_texutre)
	{
		err("error: missing texture !\n");
		exit(1);
	}
	if (config->color_celling[0] == -1 ||
		config->color_celling[1] == -1 ||
		config->color_celling[2] == -1 ||
		config->color_floor[0] == -1 ||
		config->color_floor[1] == -1 ||
		config->color_floor[2] == -1)
	{
		err("error: missing colors !\n");
		exit(1);
	}
	if (!config->map)
	{
		err("error: no map structur !\n");
		exit(1);
	}
		check_map(config->map);
}

char	*parse_texture(char *line)
{
	char	*tx;
	int		i;

	i = 3;
	while(line[i] == ' ')
		i++;
	tx = ft_strdup(&line[i]);
	tx[ft_strlen(tx - 1)] == '\0';
	return (tx);
}

void	parse_color(char *line, int *color)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
		i++;
	color[0] = ft_atoi(&line[i]);
	while(line[i] == ' ' && line[i] != ",")
		i++;
	i++;
	color[1] = ft_atoi(&line[i]);
	while(line[i] == ' ' && line[i] != ",")
		i++;
	i++;
	color[2] = ft_atoi(&line[i]);

	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255 || color[2] < 0 || color[2] > 255)
	{
		err("error: wrong rgb values\n");
		exit(1);
	}
}

void	parse_line(char *line, t_config *config)
{
	if(ft_strlen(line) <= 1)
		return;
	if (ft_strncmp(line,"NO ", 3) == 0)
		config->wn_texutre = parse_config(line);
	if (ft_strncmp(line,"SO ", 3) == 0)
		config->ws_texure = parse_config(line);
	if (ft_strncmp(line,"WE ", 3) == 0)
		config->ww_texture = parse_config(line);
	if (ft_strncmp(line,"EA ", 3) == 0)
		config->we_texture = parse_config(line);
	if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line, config->color_floor);
	if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line, config->color_celling);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if(ft_strlen(line) <= 1)
		return (0);
	while(line[i])
	{
		if ((line[i] == '0' || line[i] == '1' || line[i] == ' ' || line[i] == 'N' || line[i] == 'E' || line[i] == 'S' || line[i] == 'W'))
		{
			i++;
			continue;
		}
		else if (line[i] == '\n')
			break;
		else
			return (0);
	}
	return (1);
}

void	player_in_map(char **map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		while(map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		err("error: no player or too many players on the map !\n");
		exit(1);
	}
}

char	**parse_map(char *first_line, int fd)
{
	int		i;
	char **map;
	char *line;
	int	map_size;

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
		if (is_map_line(line))
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
		else if(map_started == 0)
			parse_line(line, &config);
		else
		{
			 err("error: please put params in right order");
			 exit(0);
		}
	}
}
