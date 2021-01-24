#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../mlx/mlx.h"
#include "constants.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void	mlx_conf(t_mlx *mlx)
{
	mlx->player.player_x = WIN_WIDTH / MINIMAP_SCALE_FACTOR / 2;
	mlx->player.player_y = WIN_HEIGHT / MINIMAP_SCALE_FACTOR / 2;
	mlx->player.width = 30 / MINIMAP_SCALE_FACTOR;
	mlx->player.height = 30 / MINIMAP_SCALE_FACTOR;
	mlx->player.rotation_angle = 270 * (M_PI / 180);
	mlx->player.walk_speed = 10 / MINIMAP_SCALE_FACTOR;
	mlx->player.turn_speed = 3 * (M_PI / 180);
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		exit(0);
	}
	if (keycode == KEY_A)
		mlx->player.player_x -= 1 * cos(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (keycode == KEY_D)
		mlx->player.player_x += 1 * cos(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (keycode == KEY_W)
		mlx->player.player_y += 1 * sin(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (keycode == KEY_S)
		mlx->player.player_y -= 1 * sin(mlx->player.rotation_angle) * mlx->player.walk_speed;
	if (keycode == KEY_A)
		mlx->player.player_y -= 1 * sin(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (keycode == KEY_D)
		mlx->player.player_y += 1 * sin(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (keycode == KEY_W)
		mlx->player.player_x += 1 * cos(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (keycode == KEY_S)
		mlx->player.player_x -= 1 * cos(mlx->player.rotation_angle) * mlx->player.walk_speed;

	if (keycode == KEY_RIGHT)
		mlx->player.rotation_angle += 1 * mlx->player.turn_speed;
	else if (keycode == KEY_LEFT)
		mlx->player.rotation_angle -= 1 * mlx->player.turn_speed;
	return (TRUE);
}

int close_button_press(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	exit(0);
	return (TRUE);
}

void put_line(t_mlx *mlx)
{
	int r = 0;
	while (r < 100)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win, mlx->player.player_x + (r * cos(mlx->player.rotation_angle)), mlx->player.player_y + (r * sin(mlx->player.rotation_angle)), 0x00FF00);
		r++;
	}
}

int rendering_loop(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->window.img_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->map.img_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->player.img_ptr, mlx->player.player_x, mlx->player.player_y);
	put_line(mlx);
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

void setting_map(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	mlx->map.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH / MINIMAP_SCALE_FACTOR, WIN_HEIGHT / MINIMAP_SCALE_FACTOR);
	mlx->map.data = (int *)mlx_get_data_addr(mlx->map.img_ptr, &(mlx->map.bpp), &(mlx->map.size_l), &(mlx->map.endian));
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			mlx->map.tile_x = x / TILE_SIZE;
			mlx->map.tile_y = y / TILE_SIZE;
			if (map[mlx->map.tile_y][mlx->map.tile_x] == 0)
				mlx->map.data[y / MINIMAP_SCALE_FACTOR * WIN_WIDTH / MINIMAP_SCALE_FACTOR + x / MINIMAP_SCALE_FACTOR] = 0x020202;
			else if (map[mlx->map.tile_y][mlx->map.tile_x] == 1)
				mlx->map.data[y / MINIMAP_SCALE_FACTOR * WIN_WIDTH / MINIMAP_SCALE_FACTOR + x / MINIMAP_SCALE_FACTOR] = 0xffffff;
		}
	}
}

void setting_player(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	mlx->player.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->player.width / MINIMAP_SCALE_FACTOR, mlx->player.height / MINIMAP_SCALE_FACTOR);
	mlx->player.data = (int *)mlx_get_data_addr(mlx->player.img_ptr, &(mlx->player.bpp), &(mlx->player.size_l), &(mlx->player.endian));
	while (++y < mlx->player.height)
	{
		x = -1;
		while (++x < mlx->player.width)
		{
			mlx->player.data[y / MINIMAP_SCALE_FACTOR * mlx->player.width / MINIMAP_SCALE_FACTOR + x / MINIMAP_SCALE_FACTOR] = 0xFFFF00;
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
	setting_map(&mlx);
	setting_player(&mlx);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &mlx);
	mlx_hook(mlx.win, 17, 1<<17, &close_button_press, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &rendering_loop, &mlx);
	mlx_loop(mlx.mlx_ptr);

	return (TRUE);
}
