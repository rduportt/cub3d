/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rduport <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:48:40 by rduport           #+#    #+#             */
/*   Updated: 2026/02/17 16:48:42 by rduport          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

typedef struct s_coordinates
{
	int	x;
	int	y;
	int	p;
	int	draw_start;
	int	draw_end;
}	t_coordinates;

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
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	camera_plane_x;
	double	camera_plane_y;
	double	camera_x;
	double	move_speed;
	double	rot_speed;
}t_player;

typedef struct s_raycasting
{
	float		raydir_x0;
	float		raydir_y0;
	float		raydir_x1;
	float		raydir_y1;
	float		pos_z;
	float		row_distance;
	float		floorstep_x;
	float		floorstep_y;
	float		floor_x;
	float		floor_y;
	int			cell_x;
	int			cell_y;
	int			tx;
	int			ty;
	uint32_t	color;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	int			orientation;
	double		raydir_x;
	double		raydir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
}t_raycasting;

typedef struct s_camera
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
}t_camera;

typedef struct s_config
{
	char	*we_texture;
	char	*ws_texure;
	char	*wn_texutre;
	char	*ww_texture;
	int		color_floor[3];
	int		color_celling[3];
	char	**map;
	int		player_i;
	int		player_j;
	char	player_direction;
	int		height;
}	t_config;

typedef struct s_data
{
	t_player	player;
	t_img		img;
	t_config	config;
	uint32_t	**buffer;
	uint32_t	*textures[8];
	void		*tex_img[8];
	int			tex_width;
	int			tex_height;
	int			tex_bits[8];
	int			tex_size_line[8];
	int			tex_endian[8];
	int			texture;
}	t_data;

// Raycasting
void		raycasting(t_data *data);
void		draw_ver_line(t_img *img, t_coordinates c, int color);
void		clear_screen(t_img *img);
int			create_rgb(int r, int g, int b);
void		draw_buffer(t_data *data);
int			close_window(t_data *data);
void		key_w(t_data *data);
void		key_s(t_data *data);
void		key_a(t_data *data);
void		key_d(t_data *data);
void		key_right(t_data *data);
void		key_left(t_data *data);
int			handle_keypress(int keycode, t_data *data);
void		horizontal_floor_raycast(t_data *data,
				t_raycasting *ray, t_coordinates *c);
void		floor_raycast(t_data *data, t_raycasting *ray, t_coordinates *c);
void		val_init(t_data *data, t_raycasting *ray, t_coordinates c);
void		is_player(t_data *data, t_raycasting *ray);
void		check_wall(t_data *data, t_raycasting *ray);
void		hit_wall(t_data *data, t_raycasting *ray);
void		dda(t_data *data, t_raycasting *ray);
void		wall_height(t_camera *cam, t_raycasting *ray);
void		texture_vertical_wall(t_data *data,
				t_raycasting *ray, t_camera *cam, t_coordinates *c);
void		texture_display(t_data *data,
				t_raycasting *ray, t_camera *cam, t_coordinates *c);
void		untextured_display(t_data *data,
				t_raycasting *ray, t_camera *cam, t_coordinates *c);
void		raycasting(t_data *data);

// Parsing
void		print_config(t_config *config);
t_config	pars_data(t_config config, char *argv);
char		**parse_map(char *first_line, int fd, int *has_extra);
void		player_in_map(char **map, t_config *config);
int			is_map_line(char *line);
void		parse_line(char *line, t_config *config);
void		parse_color(char *line, int *color);
char		*parse_texture(char *line);
void		skip_spaces(char *line, int *i);
int			count_commas(char *line, int start);
void		handle_map_line(char ***map, int *i, int *map_size, char *line);
void		process_line(char *line, t_config *config, int *map_started,
				int fd);

// Config checks
void		check_config(t_config *config);
void		check_colors(t_config *config);
void		flood_fill(int i, int j, char **map_copy, t_config *config);
void		free_map_copy(char **map_copy);
void		check_map(char **map, t_config *config);
int			get_height_map(char **map);
void		init_config(t_config *config);
void		get_player(t_config *config);

// Error handling and cleanup
int			free_data(t_data *data, int j);
void		exit_error(char *msg, t_config *config);
void		free_config(t_config *config);
int			err(char *str);

// Main hooks
void		init_camera_plane(t_data *data, t_config config);
void		init_player_direction(t_data *data, t_config config);
int			handle_keypress(int keycode, t_data *data);
int			game_loop(t_data *data);

#endif  
