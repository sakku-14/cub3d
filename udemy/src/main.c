#include <stdio.h>
#include <stdlib.h>
#include "../../mlx/mlx.h"
#include "constants.h"

void	mlx_conf(t_mlx *mlx)
{
	mlx->player.player_x = WIN_WIDTH / 2;
	mlx->player.player_y = WIN_HEIGHT / 2;
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		exit(0);
	}
	else if (keycode == KEY_LEFT)
		mlx->player.player_x -= 5;
	else if (keycode == KEY_RIGHT)
		mlx->player.player_x += 5;
	else if (keycode == KEY_UP)
		mlx->player.player_y -= 5;
	else if (keycode == KEY_DOWN)
		mlx->player.player_y += 5;
	return (TRUE);
}

int close_button_press(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	exit(0);
	return (TRUE);
}

int rendering_loop(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->window.img_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->player.player_ptr, mlx->player.player_x, mlx->player.player_y);
	return (TRUE);
}

void setting_window(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	mlx->window.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->window.data = (int *)mlx_get_data_addr(mlx->window.img_ptr, &(mlx->window.bpp), &(mlx->window.size_l), &(mlx->window.endian));
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			mlx->window.data[y * WIN_WIDTH + x] = 0x000000;
		}
	}
}

void setting_img(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	mlx->player.player_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx->player.data = (int *)mlx_get_data_addr(mlx->player.player_ptr, &(mlx->player.bpp), &(mlx->player.size_l), &(mlx->player.endian));
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			mlx->player.data[y * IMG_WIDTH + x] = 0xFFFF00;
		}
	}
}

int initialize_window(t_mlx *mlx)
{
	if (!(mlx->mlx_ptr = mlx_init()))
		return (FALSE);
	if (!(mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d_window")))
		return (FALSE);
	return (TRUE);
}

int		main()
{
	t_mlx	mlx;

	mlx_conf(&mlx);
	if (!(initialize_window(&mlx)))
		return (FALSE);
	setting_window(&mlx);
	setting_img(&mlx);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &mlx);
	mlx_hook(mlx.win, 17, 1<<17, &close_button_press, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &rendering_loop, &mlx);
	mlx_loop(mlx.mlx_ptr);

	return (TRUE);
}
