#include "cub3d.h"


int	close_window(t_img *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit(0);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 113) //Q
	{
		data->texture++;
		data->texture %= 2;
	}
	if (keycode == ESC_KEY)
		close_window(&data->img);
	//mlx_put_image_to_window(data->img.mlx, data->img.win, data->img.img, 0, 0);
	if(keycode == KEY_W)
	{
		if(data->config.worldMap[(int)data->player.posY][(int)(data->player.posX + data->player.dirX * data->player.moveSpeed)] == '0')
			data->player.posX += data->player.dirX * data->player.moveSpeed;
		if(data->config.worldMap[(int)(data->player.posY + data->player.dirY * data->player.moveSpeed)][(int)data->player.posX] == '0')
			data->player.posY += data->player.dirY * data->player.moveSpeed;
		//raycasting(data);
	}
	if(keycode == KEY_S)
	{
		if(data->config.worldMap[(int)data->player.posY][(int)(data->player.posX - data->player.dirX * data->player.moveSpeed)] == '0')
			data->player.posX -= data->player.dirX * data->player.moveSpeed;
		if(data->config.worldMap[(int)(data->player.posY - data->player.dirY * data->player.moveSpeed)][(int)data->player.posX] == '0')
			data->player.posY -= data->player.dirY * data->player.moveSpeed;
		//raycasting(data);

	}
	if(keycode == KEY_A)
	{
		if(data->config.worldMap[(int)data->player.posY][(int)(data->player.posX + (-data->player.dirY * data->player.moveSpeed))] == '0')
			data->player.posX = data->player.posX + (-data->player.dirY * data->player.moveSpeed);
		if(data->config.worldMap[(int)(data->player.posY + data->player.dirX * data->player.moveSpeed)][(int)data->player.posX] == '0')
			data->player.posY = data->player.posY + data->player.dirX * data->player.moveSpeed;
		//raycasting(data);
	}
	if(keycode == KEY_D)
	{
		if(data->config.worldMap[(int)data->player.posY][(int)(data->player.posX + data->player.dirY * data->player.moveSpeed)] == '0')
			data->player.posX = data->player.posX + data->player.dirY * data->player.moveSpeed;
		if(data->config.worldMap[(int)(data->player.posY - data->player.dirX * data->player.moveSpeed)][(int)data->player.posX] == '0')
			data->player.posY = data->player.posY - data->player.dirX * data->player.moveSpeed;
		//raycasting(data);
	}
    if(keycode == KEY_RIGHT)
    {
		//both camera direction and camera plane must be rotated
		double oldDirX = data->player.dirX;
		data->player.dirX = data->player.dirX * cos(-data->player.rotSpeed) - data->player.dirY * sin(-data->player.rotSpeed);
		data->player.dirY = oldDirX * sin(-data->player.rotSpeed) + data->player.dirY * cos(-data->player.rotSpeed);
		double oldPlaneX = data->player.cameraPlaneX;
		data->player.cameraPlaneX = data->player.cameraPlaneX * cos(-data->player.rotSpeed) - data->player.cameraPlaneY * sin(-data->player.rotSpeed);
		data->player.cameraPlaneY = oldPlaneX * sin(-data->player.rotSpeed) + data->player.cameraPlaneY * cos(-data->player.rotSpeed);
		//raycasting(data);

	}
    //rotate to the left
    if(keycode == KEY_LEFT)
    {
		//both camera direction and camera plane must be rotated
		double oldDirX = data->player.dirX;
		data->player.dirX = data->player.dirX * cos(data->player.rotSpeed) - data->player.dirY * sin(data->player.rotSpeed);
		data->player.dirY = oldDirX * sin(data->player.rotSpeed) + data->player.dirY * cos(data->player.rotSpeed);
		double oldPlaneX = data->player.cameraPlaneX;
		data->player.cameraPlaneX = data->player.cameraPlaneX * cos(data->player.rotSpeed) - data->player.cameraPlaneY * sin(data->player.rotSpeed);
		data->player.cameraPlaneY = oldPlaneX * sin(data->player.rotSpeed) + data->player.cameraPlaneY * cos(data->player.rotSpeed);
		//raycasting(data);

	}
	return (0);
}

int game_loop(t_data *data)
{
    // Vérifier les touches avec XQueryKeyMap ou garder un état
    // Mettre à jour la position du joueur
    // Appeler raycasting
    raycasting(data);
    return 0;
}

int main(int argc, char **argv)
{

	t_data			data;
	t_config		config;
	int				x;
	int				y;

	(void) argc;
	// Initialiser config
    init_config(&config);
    
    // Parser le fichier
    config = pars_data(config, argv[1]);
	print_config(&config);

	data.texture = 1;
	data.player.posX = config.player_j;
	data.player.posY = config.player_i;
	data.player.dirX = -1.5;
	data.player.dirY = 0;
	data.player.cameraPlaneX = 0;
	data.player.cameraPlaneY = 0.66;
    data.player.moveSpeed = 0.15;
    data.player.rotSpeed = 0.05;
	char *texture_files[4];

	texture_files[0] = config.wn_texutre;
	texture_files[1] = config.ws_texure;
	texture_files[2] = config.ww_texture;
	texture_files[3] = config.we_texture;
	x = -1;
	y = 0;

	int i = -1;
	while(++i < 8)
	{
		data.textures[i] = NULL;
		data.tex_img[i] = NULL;
	}



	data.img.mlx = mlx_init();
	if (!data.img.mlx)
		return (-1);
	data.img.win = mlx_new_window
		(data.img.mlx, LONGUEUR, HAUTEUR, "Cube3D");
	data.img.img = mlx_new_image(data.img.mlx, LONGUEUR, HAUTEUR);
	data.img.img_str = mlx_get_data_addr(data.img.img, &data.img.bits, &data.img.size_line, &data.img.endian);
	i = -1;
	while(++i < 4)
	{
		data.tex_img[i] = mlx_xpm_file_to_image(data.img.mlx, texture_files[i], &data.tex_height, &data.tex_width);
		if(!data.tex_img[i])
			return(printf("error loading image\n"));
		data.textures[i] = (uint32_t *)mlx_get_data_addr(data.tex_img[i], &data.tex_bits[i], &data.tex_size_line[i], &data.tex_endian[i]);
		printf("%d\n", i);
	}
	printf("abc\n");
	data.config = config;

	raycasting(&data);

	mlx_hook(data.img.win, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.img.win, DestroyNotify, StructureNotifyMask, close_window, &data.img);
	mlx_loop_hook(data.img.mlx, game_loop, &data);
	mlx_loop(data.img.mlx);	
}