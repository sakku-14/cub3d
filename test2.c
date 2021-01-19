#include "mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17

# define KEY_ESC		53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

typedef struct	s_param{
	int x;
	int y;
	char str[3];
}				t_param;

void param_init(t_param *param)
{
	param->x = 3;
	param->y = 4;
	param->str[0] = 'a';
	param->str[1] = 'b';
	param->str[2] = '\0';
}

int key_press(int key, t_param *param)
{
	if (key == KEY_W)
		param->x++;
	else if (key == KEY_S)
		param->x--;
	else if (key == KEY_ESC)
		exit(0);
	printf("x: %d\n", param->x);
	return (0);
}

int main()
{
	void	*mlx;
	void	*win;
	t_param	param;

	param_init(&param);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 700, 500, "saku1");
	mlx_hook(win, X_EVENT_KEY_PRESS, 0, &key_press, &param);
	mlx_loop(mlx);
}
