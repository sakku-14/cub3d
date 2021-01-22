#include <stdio.h>
#include <stdlib.h>
#include "../../mlx/mlx.h"
#include "constants.h"

void	param_init(t_param *param)
{
	param->x = 3;
	param->y = 4;
	param->str[0] = 'a';
	param->str[1] = 'b';
	param->str[2] = '\0';
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_LEFT)
		mlx->param.x--;
	else if (keycode == KEY_RIGHT)
		mlx->param.x++;
	else if (keycode == KEY_UP)
		mlx->param.y--;
	else if (keycode == KEY_DOWN)
		mlx->param.y++;
	return (TRUE);
}

int rendering_loop(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, mlx->param.x, mlx->param.y);
	return (TRUE);
}

int		main()
{
	t_mlx	mlx;

	param_init(&(mlx.param));
	if (!(mlx.mlx_ptr = mlx_init()))
		return (FALSE);
	if (!(mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d_window")))
		return (FALSE);

	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &(mlx.img.bpp), &(mlx.img.size_l), &(mlx.img.endian));

	int x = -1;
	int y = -1;
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			mlx.img.data[y * IMG_WIDTH + x] = 0xFFFFFF;
		}
	}

	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &rendering_loop, &mlx);
	mlx_loop(mlx.mlx_ptr);

/*
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 0, &key_press, &(mlx.param));
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, mlx.param.x, mlx.param.y);
	mlx_loop(mlx.mlx_ptr);
*/
	//mlx_destroy_window(mlx, win);
	return (TRUE);
}
