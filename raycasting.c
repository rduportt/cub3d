#include "cub3d.h"

void clear_screen(t_img *img)
{
	int total_pixels = LONGUEUR * HAUTEUR;
	unsigned int *pixel;
	int i;
	
	pixel = (unsigned int*)img->img_str;
	i = 0;
	while (i < total_pixels)
	{
		pixel[i] = 0x000000; // Noir
		i++;
	}
}

void draw_ver_line(t_img *img, int x, int y1, int y2, int color)
{
	int y;
	unsigned int *pixel;

	if (y1 < 0)
		y1 = 0;
	if (y2 >= HAUTEUR)
		y2 = HAUTEUR - 1;
	
	y = y1;
	while (y <= y2)
	{
	  pixel = (unsigned int*)(img->img_str + 
			  (y * img->size_line) + 
			  (x * (img->bits / 8)));
	  *pixel = color;
	  y++;
	}
}

void  raycasting(t_data *data)
{
	t_raycasting  ray;
	t_camera      cam;
	int           x;


	clear_screen(&data->img);
	x = -1;
	while(++x < LONGUEUR)
	{
		data->player.cameraX = 2 * x / (double)LONGUEUR - 1;
		ray.rayDirX = data->player.dirX + data->player.cameraPlaneX * data->player.cameraX;
		ray.rayDirY = data->player.dirY + data->player.cameraPlaneY * data->player.cameraX;
		ray.mapX = (int) data->player.posX;
		ray.mapY = (int) data->player.posY;

		if(ray.rayDirX == 0)
		{
			ray.deltaDistX = 1e30;
		}
		else
		{
			ray.deltaDistX = fabs(1/ray.rayDirX);
		}

		if(ray.rayDirY == 0)
		{
			ray.deltaDistY = 1e30;
		}
		else
		{
			ray.deltaDistY = fabs(1/ray.rayDirY);
		}
		ray.hit = 0;
		if(ray.rayDirX < 0)
		{
			ray.stepX = -1;
			ray.sideDistX = (data->player.posX - ray.mapX) * ray.deltaDistX;
		}
		else
		{
			ray.stepX = 1;
			ray.sideDistX = (ray.mapX + 1.0 - data->player.posX) * ray.deltaDistX;
		}
		if(ray.rayDirY < 0)
		{
			ray.stepY = -1;
			ray.sideDistY = (data->player.posY - ray.mapY) * ray.deltaDistY;
		}
		else
		{
			ray.stepY = 1;
			ray.sideDistY = (ray.mapY + 1.0 - data->player.posY) * ray.deltaDistY;
		}
		//DDA ALGO
		while(ray.hit == 0)
		{
		if(ray.sideDistX < ray.sideDistY)
		{
			ray.sideDistX += ray.deltaDistX;
			ray.mapX += ray.stepX;
			ray.side = 0;
		}
		else
		{
			ray.sideDistY += ray.deltaDistY;
			ray.mapY += ray.stepY;
			ray.side = 1;
		}
		if(worldMap[ray.mapX][ray.mapY] > 0)
			ray.hit = 1;
		}
		if(ray.side == 0)
			ray.perpWallDist = (ray.sideDistX - ray.deltaDistX);
		else
			ray.perpWallDist = (ray.sideDistY - ray.deltaDistY);
		cam.lineHeight = (int)(HAUTEUR / ray.perpWallDist);
		cam.drawStart = -cam.lineHeight / 2 + HAUTEUR / 2;
		if(cam.drawStart < 0)
			cam.drawStart = 0;
		cam.drawEnd = cam.lineHeight / 2 + HAUTEUR / 2;
		if(cam.drawEnd >= HAUTEUR)
			cam.drawEnd = HAUTEUR - 1;
		if(worldMap[ray.mapX][ray.mapY] == 1)
			cam.color = 0xFF0000;
		else if(worldMap[ray.mapX][ray.mapY] == 2)
			cam.color = 0x00FF00;
		else if(worldMap[ray.mapX][ray.mapY] == 3)
			cam.color = 0x0000FF;
		else if(worldMap[ray.mapX][ray.mapY] == 4)
			cam.color = 0xFFFFFF;
		else
			cam.color = 0xFFFF00;
		if(ray.side == 1)
			cam.color = ((cam.color >> 1) & 0x7F7F7F);
		draw_ver_line(&data->img, x, cam.drawStart, cam.drawEnd, cam.color);
	}
	mlx_put_image_to_window(data->img.mlx, data->img.win, data->img.img, 0, 0);

}