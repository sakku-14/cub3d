#include "mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int deal_key(int key, void *param)
{
//	ft_putchar('X');
	printf("%d\n", key);
	return (0);
}

int main()
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 700, 500, "saku1");
	mlx_key_hook(win, deal_key, (void *)0);
	mlx_loop(mlx);
}
