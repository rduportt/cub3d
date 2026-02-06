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
	if (keycode == ESC_KEY)
		close_window(&data->img);
	mlx_put_image_to_window(data->img.mlx, data->img.win, data->img.img, 0, 0);
	if(keycode == KEY_W)
	{
		if(worldMap[(int)(data->player.posX + data->player.dirX * 0.06)][(int)data->player.posY] == 0)
			data->player.posX += data->player.dirX * 0.05;
		if(worldMap[(int)data->player.posY][(int)(data->player.posY + data->player.dirY * 0.06)] == 0)
			data->player.posY += data->player.dirY * 0.05;
		raycasting(data);
	}
	if(keycode == KEY_S)
	{
		if(worldMap[(int)(data->player.posX - data->player.dirX * 0.05)][(int)data->player.posY] == 0)
			data->player.posX -= data->player.dirX * 0.05;
		if(worldMap[(int)data->player.posY][(int)(data->player.posY - data->player.dirY * 0.05)] == 0)
			data->player.posY -= data->player.dirY * 0.05;
		raycasting(data);

	}
    if(keycode == KEY_D)
    {
		//both camera direction and camera plane must be rotated
		double oldDirX = data->player.dirX;
		data->player.dirX = data->player.dirX * cos(-0.03) - data->player.dirY * sin(-0.03);
		data->player.dirY = oldDirX * sin(-0.03) + data->player.dirY * cos(-0.03);
		double oldPlaneX = data->player.cameraPlaneX;
		data->player.cameraPlaneX = data->player.cameraPlaneX * cos(-0.03) - data->player.cameraPlaneY * sin(-0.03);
		data->player.cameraPlaneY = oldPlaneX * sin(-0.03) + data->player.cameraPlaneY * cos(-0.03);
		raycasting(data);

	}
    //rotate to the left
    if(keycode == KEY_A)
    {
		//both camera direction and camera plane must be rotated
		double oldDirX = data->player.dirX;
		data->player.dirX = data->player.dirX * cos(0.05) - data->player.dirY * sin(0.05);
		data->player.dirY = oldDirX * sin(0.05) + data->player.dirY * cos(0.05);
		double oldPlaneX = data->player.cameraPlaneX;
		data->player.cameraPlaneX = data->player.cameraPlaneX * cos(0.05) - data->player.cameraPlaneY * sin(0.05);
		data->player.cameraPlaneY = oldPlaneX * sin(0.05) + data->player.cameraPlaneY * cos(0.05);
		raycasting(data);

	}
	return (0);
}

int main(int argc, char **argv)
{
  t_data        data;
  t_raycasting  ray;
  t_camera      cam;
  int       x;
  int       y;

  data.player.posX = 22;
  data.player.posY = 11;
  data.player.dirX = -1.5;
  data.player.dirY = 0;
  data.player.cameraPlaneX = 0;
  data.player.cameraPlaneY = 0.66;
  x = -1;
  y = 0;

  data.img.mlx = mlx_init();
  if (!data.img.mlx)
	return (-1);
  data.img.win = mlx_new_window
	(data.img.mlx, LONGUEUR, HAUTEUR, "Cube3D");
  data.img.img = mlx_new_image(data.img.mlx, LONGUEUR, HAUTEUR);
  data.img.img_str = mlx_get_data_addr
	(data.img.img, &data.img.bits, &data.img.size_line, &data.img.endian);

	raycasting(&data);


	mlx_hook(data.img.win, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook(data.img.win, DestroyNotify, StructureNotifyMask, close_window, &data.img);
	mlx_loop(data.img.mlx);	
}