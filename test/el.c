#include "mlx/mlx.h"

int main()
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 700, 500, "saku1");
	int x = 0;
	while (x < 700)
	{
		mlx_pixel_put(mlx, win, x, 250, 0xFFFFFF);
		x++;
	}
	mlx_loop(mlx);
}
