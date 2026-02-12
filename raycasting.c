#include "cub3d.h"


int create_rgb(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

void draw_buffer(t_data *data)
{
	int y;
	unsigned int *dst;
	
	dst = (unsigned int *)data->img.img_str;
	y = 0;
	while (y < HAUTEUR)
	{
		memcpy(dst + (y * LONGUEUR), 
			   data->buffer[y], 
			   LONGUEUR * sizeof(unsigned int));
		y++;
	}
}

void clear_screen(t_img *img)
{
	int total_pixels = LONGUEUR * HAUTEUR;
	unsigned int *pixel;
	int i;
	
	pixel = (unsigned int*)img->img_str;
	i = 0;
	while (i < total_pixels)
	{
		pixel[i] = 0x000000;
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

void raycasting(t_data *data)
{
	t_raycasting ray;
	t_camera cam;
	int x;
	int y;
	int p;

	clear_screen(&data->img);
	x = -1;
	y = -1;
	if(data->texture == 1)
	{
		while(++y < HAUTEUR)
		{
			ray.rayDirX0 = data->player.dirX - data->player.cameraPlaneX;
			ray.rayDirY0 = data->player.dirY - data->player.cameraPlaneY;
			ray.rayDirX1 = data->player.dirX + data->player.cameraPlaneX;
			ray.rayDirY1 = data->player.dirY + data->player.cameraPlaneY;
			p = y - HAUTEUR / 2;
			ray.posZ = 0.5 * HAUTEUR;
			ray.rowDistance = ray.posZ / p;
			ray.floorstepX = ray.rowDistance * (ray.rayDirX1 - ray.rayDirX0) / LONGUEUR;
			ray.floorstepY = ray.rowDistance * (ray.rayDirY1 - ray.rayDirY0) / LONGUEUR;
			ray.floorX = data->player.posX + ray.rowDistance * ray.rayDirX0;
			ray.floorY = data->player.posY + ray.rowDistance * ray.rayDirY0;
			x = -1;
			while(++x < LONGUEUR)
			{
				ray.cellX = (int)ray.floorX;
				ray.cellY = (int)ray.floorY;
				ray.tx = (int)(data->tex_width * (ray.floorX - ray.cellX)) & (data->tex_width - 1);
				ray.ty = (int)(data->tex_height * (ray.floorY - ray.cellY)) & (data->tex_height - 1);
				ray.floorX += ray.floorstepX;
				ray.floorY += ray.floorstepY;
				ray.color = create_rgb(data->config.color_floor[0], data->config.color_floor[1], data->config.color_floor[2]);
				data->buffer[y][x] = ray.color;
				ray.color = create_rgb(data->config.color_celling[0], data->config.color_celling[1], data->config.color_celling[2]);
				data->buffer[HAUTEUR - y - 1][x] = ray.color;
			}
		}
	}
	x = -1;
	while(++x < LONGUEUR)
	{
		data->player.cameraX = 2 * x / (double)LONGUEUR - 1;
		ray.rayDirX = data->player.dirX + data->player.cameraPlaneX * data->player.cameraX;
		ray.rayDirY = data->player.dirY + data->player.cameraPlaneY * data->player.cameraX;
		ray.mapX = (int) data->player.posX;
		ray.mapY = (int) data->player.posY;
		if(ray.rayDirX == 0)
			ray.deltaDistX = 1e30;
		else
			ray.deltaDistX = fabs(1/ray.rayDirX);
		if(ray.rayDirY == 0)
			ray.deltaDistY = 1e30;
		else
			ray.deltaDistY = fabs(1/ray.rayDirY);
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
			if(data->config.worldMap[ray.mapY][ray.mapX] != '0')
				ray.hit = 1;
		}
		if(ray.side == 0)
			ray.perpWallDist = (ray.sideDistX - ray.deltaDistX);
		else
			ray.perpWallDist = (ray.sideDistY - ray.deltaDistY);
		cam.lineHeight = (int)(HAUTEUR / ray.perpWallDist);
		cam.drawStart = -cam.lineHeight / 2 + HAUTEUR / 2;
		if(data->texture == 1)
		{
			if(cam.drawStart < 0)
				cam.drawStart = 0;
			cam.drawEnd = cam.lineHeight / 2 + HAUTEUR / 2;
			if(cam.drawEnd >= HAUTEUR)
				cam.drawEnd = HAUTEUR - 1;
			if(ray.side == 1)
					{
				if(ray.rayDirY > 0)
					ray.orientation = 0; // NORD
				else
					ray.orientation = 1; // SUD
			}
			else
			{
				if(ray.rayDirX > 0)
					ray.orientation = 2; // OUEST
				else
					ray.orientation = 3; // EST
			}
			if(data->config.worldMap[ray.mapY][ray.mapX] == 'N' || data->config.worldMap[ray.mapY][ray.mapX] == 'S' || data->config.worldMap[ray.mapY][ray.mapX] == 'E' || data->config.worldMap[ray.mapY][ray.mapX] == 'W')
				data->config.worldMap[ray.mapY][ray.mapX] = '0';
			ray.texNum = ((data->config.worldMap[ray.mapY][ray.mapX] - '0') - 1) + ray.orientation;
			if(ray.side == 0)
				ray.wallX = data->player.posY + ray.perpWallDist * ray.rayDirY;
			else
				ray.wallX = data->player.posX + ray.perpWallDist * ray.rayDirX;
			ray.wallX -= floor(ray.wallX);
			ray.texX = (int)(ray.wallX * (double)data->tex_width);
			if(ray.side == 0 && ray.rayDirX > 0)
				ray.texX = data->tex_width - ray.texX - 1;
			if(ray.side == 1 && ray.rayDirY < 0)
				ray.texX = data->tex_width - ray.texX - 1;
			ray.step = 1.0 * data->tex_height / cam.lineHeight;
			ray.texPos = (cam.drawStart - HAUTEUR / 2 + cam.lineHeight / 2) * ray.step;
			y = cam.drawStart;
			while(++y < cam.drawEnd)
			{
				ray.texY = (int)ray.texPos & (data->tex_height - 1);
				ray.texPos += ray.step;
				ray.color = data->textures[ray.texNum][data->tex_width * ray.texY + ray.texX];
				if(ray.side == 1)
					ray.color = (ray.color >> 1) & 8355711;
				data->buffer[y][x] = ray.color;
			}
		}
		else
		{
			if(cam.drawStart < 0)
				cam.drawStart = 0;
			cam.drawEnd = cam.lineHeight / 2 + HAUTEUR / 2;
			if(cam.drawEnd >= HAUTEUR)
				cam.drawEnd = HAUTEUR - 1;
			if(data->config.worldMap[ray.mapY][ray.mapX] == '1')
				cam.color = 0xFF0000;
			else
				cam.color = 0xFFFF00;
			if(ray.side == 1)
				cam.color = ((cam.color >> 1) & 0x7F7F7F);
			draw_ver_line(&data->img, x, cam.drawStart, cam.drawEnd, cam.color);			
		}
	}
	if(data->texture == 1)
		draw_buffer(data);
	data->player.moveSpeed = 0.1;
	data->player.rotSpeed = 0.06;
	mlx_put_image_to_window(data->img.mlx, data->img.win, data->img.img, 0, 0);
}