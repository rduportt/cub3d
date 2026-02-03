#include "cub3d.h"

int	close_window(t_img *img)
{
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit(0);
}

int	handle_keypress(int keycode, t_img *img)
{
	if (keycode == ESC_KEY)
		close_window(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
    t_img	img;
    img.mlx = mlx_init();
		if (!img.mlx)
			return (-1);
		img.win = mlx_new_window
			(img.mlx, LONGUEUR, HAUTEUR, "Cube3D");
		img.img = mlx_new_image(img.mlx, LONGUEUR, HAUTEUR);
		img.img_str = mlx_get_data_addr
			(img.img, &img.bits, &img.size_line, &img.endian);
	    mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	    mlx_hook(img.win, KeyPress, KeyPressMask, handle_keypress, &img);
	    mlx_hook(img.win, DestroyNotify, StructureNotifyMask, close_window, &img);
        mlx_loop(img.mlx);	
}