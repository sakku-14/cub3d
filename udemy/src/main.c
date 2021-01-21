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
	return (TRUE);
}

int		main()
{
	void *mlx;
	void *win;
	t_param	param;

	param_init(&param);
	if (!(mlx = mlx_init()))
		return (FALSE);
	if (!(win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d_window")))
		return (FALSE);
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
	mlx_loop(mlx);
	//mlx_destroy_window(mlx, win);
	return (TRUE);
}
