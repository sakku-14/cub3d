#include "mlx/mlx.h"
#include <stdio.h>

int main()
{
	void	*mlx;
	void	*win;
	void	*img;

	int		img_width;
	int		img_height;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 700, 500, "saku1");
	img = mlx_xpm_file_to_image(mlx, "textures/wall_n.xpm", &img_width, &img_height);
	mlx_put_image_to_window(mlx, win, img, 350, 250);
	mlx_loop(mlx);
}
