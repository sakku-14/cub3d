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

int	key_press(int keycode, t_param *param)
{
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_LEFT)
		param->x--;
	else if (keycode == KEY_RIGHT)
		param->x++;
	else if (keycode == KEY_UP)
		param->y++;
	else if (keycode == KEY_DOWN)
		param->y--;
	return (TRUE);
}

int		main()
{
	t_mlx	*mlx;
	t_param	param;
	t_img	img;

	param_init(&param);
	if (!(mlx->mlx_ptr = mlx_init()))
		return (FALSE);
	if (!(mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3d_window")))
		return (FALSE);

	img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

	int x = -1;
	int y = -1;
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			img.data[y * IMG_WIDTH + x] = 0xFFFFFF;
		}
	}

	mlx_hook(mlx->win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, param.x, param.y);
	mlx_loop(mlx->mlx_ptr);
	//mlx_destroy_window(mlx, win);
	return (TRUE);
}
