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
	if (config->worldMap)
	{
		while (config->worldMap[i])
			free(config->worldMap[i++]);
		free(config->worldMap);
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
	while (config->worldMap[i])
	{
		j = 0;
		while (config->worldMap[i][j])
		{
			if (config->worldMap[i][j] == 'N' || config->worldMap[i][j] == 'E' || config->worldMap[i][j] == 'S' || config->worldMap[i][j] == 'W')
			{
				config->player_i = i;
				config->player_j = j;
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
	config->worldMap = NULL;
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

void	check_map(char **map, t_config *config)
{
	int	i;
	int	j;
	int	player_i;
	int	player_j;
	int	height;
	char	**map_copy;
	
	player_in_map(map, config);
	player_i = 0;
	player_j = 0;
	height = get_height_map(map);
	map_copy = malloc(sizeof(char*) * (height + 1));
	i = 0;
	while (map[i])
	{
		map_copy[i] = ft_strdup(map[i]);
		i++;
	}
	map_copy[i] = NULL;
	i = 0;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == 'N' || map_copy[i][j] == 'E' || map_copy[i][j] == 'S' || map_copy[i][j] == 'W')
			{
				player_i = i;
				player_j = j;
			}
			j++;
		}
		i++;
	}
	flood_fill(player_i, player_j, height, map_copy, config);
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

void	flood_fill(int i, int j, int height, char ** map_copy, t_config *config)
{
	if (i < 0 || i >= height || j < 0 || !map_copy[i][j] || map_copy[i][j] == '\n' || map_copy[i][j] == ' ')
	{
		free_map_copy(map_copy);
		exit_error("error: map not closed !\n", config);
	}
	if (map_copy[i][j] == '1' || map_copy[i][j] == 'X')
		return;	
	map_copy[i][j] = 'X';

	flood_fill(i + 1, j, height, map_copy, config);
	flood_fill(i, j + 1, height, map_copy, config);
	flood_fill(i - 1, j, height, map_copy, config);
	flood_fill(i, j - 1, height, map_copy, config);
}

void	check_colors(t_config *config)
{
	if (config->color_floor[0] < 0 ||
		config->color_floor[0] > 255 ||
		config->color_floor[1] < 0 ||
		config->color_floor[1] > 255 ||
		config->color_floor[2] < 0 ||
		config->color_floor[2] > 255 ||
		config->color_celling[0] < 0 ||
		config->color_celling[0] > 255 ||
		config->color_celling[1] < 0 ||
		config->color_celling[1] > 255 ||
		config->color_celling[2] < 0||
		config->color_celling[2] > 255)
		exit_error("error: bad RGB values\n", config);
}

void	check_config(t_config *config)
{
	if (!config->ws_texure || !config->ww_texture || !config->we_texture || !config->wn_texutre)
		exit_error("error: missing texture !\n",config);
	if (config->color_celling[0] == -1 ||
		config->color_celling[1] == -1 ||
		config->color_celling[2] == -1 ||
		config->color_floor[0] == -1 ||
		config->color_floor[1] == -1 ||
		config->color_floor[2] == -1)
		exit_error("error: missing colors !\n", config);
	check_colors(config);
	if (!config->worldMap)
		exit_error("error: no map structur !\n", config);
	check_map(config->worldMap, config);
}

char	*parse_texture(char *line)
{
	char	*tx;
	int		i;

	i = 3;
	while(line[i] == ' ')
		i++;
	tx = ft_strdup(&line[i]);
	tx[ft_strlen(tx) - 1] = '\0';
	return (tx);
}

void	parse_color(char *line, int *color)
{
	int	i;
	int	count;
	int	j;

	i = 2;
	while (line[i] == ' ')
		i++;
	count = 0;
	j = i;
	while (line[j] && line[j] != '\n')
	{
		if (line[j] == ',')
			count++;
		j++;
	}
	if (count != 2)
		return;
	while (line[i] == ' ')
		i++;
	if (!ft_isdigit(line[i]))
		return;
	color[0] = ft_atoi(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != ',')
		return;
	i++;
	while (line[i] == ' ')
		i++;
	if (!ft_isdigit(line[i]))
		return;
	color[1] = ft_atoi(&line[i]);
	while (line[i] && ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] != ',')
		return;
	i++;
	while (line[i] == ' ')
		i++;
	if (!ft_isdigit(line[i]))
		return;
	color[2] = ft_atoi(&line[i]);
}

void	parse_line(char *line, t_config *config)
{
	if(ft_strlen(line) <= 1)
		return;
	if (ft_strncmp(line,"NO ", 3) == 0)
		config->wn_texutre = parse_texture(line);
	if (ft_strncmp(line,"SO ", 3) == 0)
		config->ws_texure = parse_texture(line);
	if (ft_strncmp(line,"WE ", 3) == 0)
		config->ww_texture = parse_texture(line);
	if (ft_strncmp(line,"EA ", 3) == 0)
		config->we_texture = parse_texture(line);
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
		while(map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		exit_error("error: no player or too many players on the map !\n", config);
}

char	**parse_map(char *first_line, int fd, t_config *config)
{
	int		i;
	char **map;
	char *line;
	int	map_size;

	i = 0;
	map_size = 100;
	map = malloc(sizeof(char*) * map_size);

	map[i++] = ft_strdup(first_line);
	while((line = get_next_line(fd)))
	{
		if (ft_strlen(line) <= 1)
		{
			free(line);
			continue;
		}
		if (is_map_line(line))
		{
			if (i >= map_size)
			{
				map_size *= 2;
				map = realloc(map, sizeof(char*) * map_size);
			}
			map[i++] = ft_strdup(line);
		}
		else
		{
			free(line);
			exit_error("error: invalid content after map !\n", config);
		}
		free(line);
	}
	map[i] = NULL;
	return (map);
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
	while ((line = get_next_line(fd)))
	{
		if (is_map_line(line))
		{
			map_started = 1;
			config.worldMap = parse_map(line, fd, &config);
			free(line);
			break;
		}
		else if(map_started == 0)
			parse_line(line, &config);
		free(line);
	}
	close(fd);
	check_config(&config);
	get_player(&config);
	return (config);
}

#include "cub3d.h"

void print_config(t_config *config)
{
    int i;
    
    printf("\n=== CONFIGURATION ===\n\n");
    
    // Textures
    printf("Textures:\n");
    printf("  NO: %s\n", config->wn_texutre ? config->wn_texutre : "NULL");
    printf("  SO: %s\n", config->ws_texure ? config->ws_texure : "NULL");
    printf("  WE: %s\n", config->we_texture ? config->we_texture : "NULL");
    printf("  EA: %s\n", config->ww_texture ? config->ww_texture : "NULL");
    // Couleurs
    printf("\nColors:\n");
    printf("  Floor (F):   R=%d, G=%d, B=%d\n", 
           config->color_floor[0], 
           config->color_floor[1], 
           config->color_floor[2]);
    printf("  Ceiling (C): R=%d, G=%d, B=%d\n", 
           config->color_celling[0], 
           config->color_celling[1], 
           config->color_celling[2]);
    
    // Map
    printf("\nMap:\n");
    if (config->worldMap)
    {
        i = 0;
        while (config->worldMap[i])
        {
            printf("  [%02d] %s", i, config->worldMap[i]);
            i++;
        }
        printf("\nMap height: %d lines\n", i);
    }
    else
    {
        printf("  NULL\n");
    }
    printf("\n=== END ===\n\n");
}

int main(int argc, char **argv)
{

	(void)argc;
	(void)**argv;
    t_config config;
    
    printf("Starting parser...\n");
    
    // Initialiser config
    init_config(&config);
    
    // Parser le fichier
    config = pars_data(config);

	// Afficher le résultat
    print_config(&config);
    
    printf("✓ Parsing successful!\n");
    
    // Free (optionnel pour tester)
    if (config.worldMap)
    {
        int i = 0;
        while (config.worldMap[i])
            free(config.worldMap[i++]);
        free(config.worldMap);
    }
    if (config.wn_texutre)
        free(config.wn_texutre);
    if (config.ws_texure)
        free(config.ws_texure);
    if (config.we_texture)
        free(config.we_texture);
    if (config.ww_texture)
        free(config.ww_texture);
    
    return (0);
}