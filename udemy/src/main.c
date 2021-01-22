#include <stdio.h>
#include <stdlib.h>
#include "../../mlx/mlx.h"
#include "constants.h"

void	mlx_setup(t_mlx *mlx)
{
	mlx->param.x = WIN_WIDTH / 2;
	mlx->param.y = WIN_HEIGHT / 2;
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_LEFT)
		mlx->param.x -= 5;
	else if (keycode == KEY_RIGHT)
		mlx->param.x += 5;
	else if (keycode == KEY_UP)
		mlx->param.y -= 5;
	else if (keycode == KEY_DOWN)
		mlx->param.y += 5;
	return (TRUE);
}

int rendering_loop(t_mlx *mlx)
{
	int x = -1;
	int y = -1;
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			mlx->img.data[y * IMG_WIDTH + x] = 0xFFFFFF;
		}
	}

	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->window.img_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, mlx->param.x, mlx->param.y);
	return (TRUE);
}

void initialize_window(t_mlx *mlx)
{
	mlx->window.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->window.data = (int *)mlx_get_data_addr(mlx->window.img_ptr, &(mlx->window.bpp), &(mlx->window.size_l), &(mlx->window.endian));
	int x = -1;
	int y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			mlx->window.data[y * WIN_WIDTH + x] = 0x000000;
		}
	}
}

int		main()
{
	t_mlx	mlx;

	mlx_setup(&mlx);
	if (!(mlx.mlx_ptr = mlx_init()))
		return (FALSE);
	if (!(mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d_window")))
		return (FALSE);

	initialize_window(&mlx);
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &(mlx.img.bpp), &(mlx.img.size_l), &(mlx.img.endian));
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &rendering_loop, &mlx);
	mlx_loop(mlx.mlx_ptr);

	return (TRUE);
}
