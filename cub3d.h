#ifndef CUBE3D_H
# define CUBE3D_H

# include "libft/libft.h"
# include "get_next_line/get_next_line_bonus.h"
# include "unistd.h"
# include "mlx.h"
# include "X11/X.h"
# include <stdlib.h>
# include <stdio.h>
# include "string.h"
# include <math.h>
# include <sys/time.h>
# include <time.h>
# include <stdint.h>
#define mapWidth 24
#define mapHeight 24
# define HAUTEUR 1080
# define LONGUEUR 1920
# define ESC_KEY 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_W 119 
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100


typedef struct s_img
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_str;
	int		bits;
	int		size_line;
	int		endian;
}t_img;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	cameraPlaneX;
	double	cameraPlaneY;
	double	cameraX;
	double	moveSpeed;
	double	rotSpeed;
}t_player;

typedef	struct s_raycasting
{
	//floor + ceilling
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	float	posZ;
	float	rowDistance;
	float	floorstepX;
	float	floorstepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
	int		floorTexture;
	int		ceilingTexture;
	uint32_t	color;

	//wall
	int		texNum;
	double	wallX;
	int		texX;
	int		texY;
	double	step;
	double	texPos;
	int		orientation;

	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
}t_raycasting;

typedef struct	s_camera
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int	color;
}t_camera;

typedef struct s_config
{
    char    *we_texture;
    char    *ws_texure;
    char    *wn_texutre;
    char    *ww_texture;
    int        color_floor[3];
    int        color_celling[3];
    char    **worldMap;
	int		player_i;
	int		player_j;
} t_config;

typedef struct s_data
{
    t_player    player;
    t_img       img;
	t_config	config;
	uint32_t		buffer[HAUTEUR][LONGUEUR];
	uint32_t		*textures[8];
	void			*tex_img[8];
	int 		tex_width;
    int 		tex_height;
	int         tex_bits[8];
    int         tex_size_line[8];
    int         tex_endian[8];
	int			texture;
}   t_data;



void		raycasting(t_data *data);
void 		draw_ver_line(t_img *img, int x, int y1, int y2, int color);
void 		clear_screen(t_img *img);
void 		print_config(t_config *config);
t_config	pars_data(t_config config, char *argv);
char		**parse_map(char *first_line, int fd, t_config *config);
void		player_in_map(char **map, t_config *config);
int			is_map_line(char *line);
void		parse_line(char *line, t_config *config);
void		parse_color(char *line, int *color);
char		*parse_texture(char *line);
void		check_config(t_config *config);
void		flood_fill(int i, int j, int height, char ** map_copy, t_config *config);
void		free_map_copy(char **map_copy);
void		check_map(char **map, t_config *config);
int			get_height_map(char **map);
void		init_config(t_config *config);
void		exit_error(char *msg, t_config *config);
void		free_config(t_config *config);
int			err(char *str);



#endif  