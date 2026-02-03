#ifndef CUBE3D_H
# define CUBE3D_H

# include "unistd.h"
# include "mlx.h"
# include "X11/X.h"
# include "stdlib.h"
# include "stdio.h"
# include "string.h"
# include "math.h"
# define HAUTEUR 1000
# define LONGUEUR 1000

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

#endif  