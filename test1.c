#include "mlx/mlx.h"

int main()
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 700, 500, "saku1");
	mlx_loop(mlx);
}
