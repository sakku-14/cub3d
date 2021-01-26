#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "../../mlx/mlx.h"
#include "constants.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

float dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * ( x1 - x2 ) + (y1 - y2) * (y1 - y2)));
}

void	mlx_conf(t_mlx *mlx)
{
	mlx->player.player_x = WIN_WIDTH / 2;
	mlx->player.player_y = WIN_HEIGHT / 2;
	mlx->player.width = 4;
	mlx->player.height = 4;
	mlx->player.rotation_angle = 90 * (M_PI / 180);
	mlx->player.walk_speed = 5;
	mlx->player.turn_speed = 4 * (M_PI / 180);
}

int	map_has_wall_at(float x, float y)
{
	int map_grid_index_x;
	int map_grid_index_y;
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (TRUE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return (map[map_grid_index_y][map_grid_index_x] != 0);
}

int	key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		exit(0);
	}
	if (key == KEY_W)
		mlx->player.walk_direction = +1;
	if (key == KEY_S)
		mlx->player.walk_direction = -1;
	if (key == KEY_D)
		mlx->player.side_direction = +1;
	if (key == KEY_A)
		mlx->player.side_direction = -1;
	if (key == KEY_RIGHT)
		mlx->player.turn_direction = +1;
	if (key == KEY_LEFT)
		mlx->player.turn_direction = -1;
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
	while (r < 200 / MINIMAP_SCALE_FACTOR)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win, (mlx->player.player_x + r * cos(mlx->player.rotation_angle)) / MINIMAP_SCALE_FACTOR, (mlx->player.player_y + r * sin(mlx->player.rotation_angle)) / MINIMAP_SCALE_FACTOR, 0x00FF00);
		r++;
	}
}

void move(t_mlx *mlx)
{
	float new_player_x = mlx->player.player_x;
	float new_player_y = mlx->player.player_y;

	if (mlx->player.side_direction == -1)
		new_player_x = mlx->player.player_x - cos(mlx->player.rotation_angle + M_PI / 2) * mlx->player.walk_speed;
	else if (mlx->player.side_direction == 1)
		new_player_x = mlx->player.player_x + cos(mlx->player.rotation_angle + M_PI / 2) * mlx->player.walk_speed;
	else if (mlx->player.walk_direction == 1)
		new_player_y = mlx->player.player_y + sin(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (mlx->player.walk_direction == -1)
		new_player_y = mlx->player.player_y - sin(mlx->player.rotation_angle) * mlx->player.walk_speed;
	if (mlx->player.side_direction == -1)
		new_player_y = mlx->player.player_y - sin(mlx->player.rotation_angle + M_PI / 2) * mlx->player.walk_speed;
	else if (mlx->player.side_direction == 1)
		new_player_y = mlx->player.player_y + sin(mlx->player.rotation_angle + M_PI / 2) * mlx->player.walk_speed;
	else if (mlx->player.walk_direction == 1)
		new_player_x = mlx->player.player_x + cos(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (mlx->player.walk_direction == -1)
		new_player_x = mlx->player.player_x - cos(mlx->player.rotation_angle) * mlx->player.walk_speed;

	if (mlx->player.turn_direction == 1)
		mlx->player.rotation_angle += 1 * mlx->player.turn_speed;
	else if (mlx->player.turn_direction == -1)
		mlx->player.rotation_angle -= 1 * mlx->player.turn_speed;

	if (!map_has_wall_at(new_player_x, new_player_y))
	{
		mlx->player.player_x = new_player_x;
		mlx->player.player_y = new_player_y;
	}
}

float normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void cast_ray(float ray_angle, int strip_id, t_mlx *mlx)
{
	ray_angle = normalize_angle(ray_angle);

	int is_ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
	int is_ray_facing_up = !is_ray_facing_down;
	int is_ray_facing_right = ray_angle < M_PI / 2 || ray_angle > M_PI * 3 / 2;
	int is_ray_facing_left = !is_ray_facing_right;

	float x_intercept, y_intercept, x_step, y_step;
	
	///////////////////////////////////////////
	// horizontal ray_grid intersection code
	///////////////////////////////////////////
	int found_horz_wall_hit = FALSE;
	float horz_wall_hit_x = 0;
	float horz_wall_hit_y = 0;
	int horz_wall_content = 0;

	y_intercept = floor(mlx->player.player_y / TILE_SIZE) * TILE_SIZE;
	y_intercept += is_ray_facing_down ? TILE_SIZE : 0;
	x_intercept = mlx->player.player_x + (y_intercept - mlx->player.player_y) / tan(ray_angle);
	y_step = TILE_SIZE;
	y_step *= is_ray_facing_up ? -1 : 1;
	x_step = TILE_SIZE / tan(ray_angle);
	x_step *= (is_ray_facing_left && x_step > 0) ? -1 : 1;
	x_step *= (is_ray_facing_right && x_step < 0) ? -1 : 1;

	float next_horz_touch_x = x_intercept;
	float next_horz_touch_y = y_intercept;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= WIN_WIDTH && next_horz_touch_y >= 0 && next_horz_touch_y <= WIN_HEIGHT)
	{
		float x_to_check = next_horz_touch_x;
		float y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);
		if (map_has_wall_at(x_to_check, y_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			found_horz_wall_hit = TRUE;
			break;
		}
		else
		{
			next_horz_touch_x += x_step;
			next_horz_touch_y += y_step;
		}
	}

	///////////////////////////////////////////
	// vertical ray_grid intersection code
	///////////////////////////////////////////
	int found_vert_wall_hit = FALSE;
	float vert_wall_hit_x = 0;
	float vert_wall_hit_y = 0;
	int vert_wall_content = 0;

	x_intercept = floor(mlx->player.player_x / TILE_SIZE) * TILE_SIZE;
	x_intercept += is_ray_facing_right ? TILE_SIZE : 0;
	y_intercept = mlx->player.player_y + (x_intercept - mlx->player.player_x) * tan(ray_angle);
	x_step = TILE_SIZE;
	x_step *= is_ray_facing_left ? -1 : 1;
	y_step = TILE_SIZE * tan(ray_angle);
	y_step *= (is_ray_facing_up && y_step > 0) ? -1 : 1;
	y_step *= (is_ray_facing_down && y_step < 0) ? -1 : 1;

	float next_vert_touch_x = x_intercept;
	float next_vert_touch_y = y_intercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WIN_WIDTH && next_vert_touch_y >= 0 && next_vert_touch_y <= WIN_HEIGHT)
	{
		float x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
		float y_to_check = next_vert_touch_y;
		if (map_has_wall_at(x_to_check, y_to_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			found_vert_wall_hit = TRUE;
			break;
		}
		else
		{
			next_vert_touch_x += x_step;
			next_vert_touch_y += y_step;
		}
	}

	float horz_hit_distance = found_horz_wall_hit
		? dist_between_points(mlx->player.player_x, mlx->player.player_y, horz_wall_hit_x, horz_wall_hit_y)
		: FLT_MAX;
	float vert_hit_distance = found_vert_wall_hit
		? dist_between_points(mlx->player.player_x, mlx->player.player_y, vert_wall_hit_x, vert_wall_hit_y)
		: FLT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		mlx->rays[strip_id].distance = vert_hit_distance;
		mlx->rays[strip_id].wall_hit_x = vert_wall_hit_x;
		mlx->rays[strip_id].wall_hit_y = vert_wall_hit_y;
		mlx->rays[strip_id].wall_hit_content = vert_wall_content;
		mlx->rays[strip_id].was_hit_vertical = TRUE;
	} else {
		mlx->rays[strip_id].distance = horz_hit_distance;
		mlx->rays[strip_id].wall_hit_x = horz_wall_hit_x;
		mlx->rays[strip_id].wall_hit_y = horz_wall_hit_y;
		mlx->rays[strip_id].wall_hit_content = horz_wall_content;
		mlx->rays[strip_id].was_hit_vertical = FALSE;
	}
	mlx->rays[strip_id].ray_angle = ray_angle;
	mlx->rays[strip_id].is_ray_facing_down = is_ray_facing_down;
	mlx->rays[strip_id].is_ray_facing_up = is_ray_facing_up;
	mlx->rays[strip_id].is_ray_facing_left = is_ray_facing_left;
	mlx->rays[strip_id].is_ray_facing_right = is_ray_facing_right;
}

void cast_all_rays(t_mlx *mlx)
{
	int		strip_id;
	float	ray_angle;

	strip_id = 0;
	ray_angle = mlx->player.rotation_angle - (FOV_ANGLE / 2);
	while (strip_id < NUM_RAYS)
	{
		cast_ray(ray_angle, strip_id, mlx);
		strip_id++;
		ray_angle += FOV_ANGLE / NUM_RAYS;
	}
}

void setting_ray_point(t_mlx *mlx)
{
	int x = -1;
	int y = -1;
	int i = 0;

	while (i < NUM_RAYS)
	{
		mlx->rays[i].img_ptr = mlx_new_image(mlx->mlx_ptr, 20 / MINIMAP_SCALE_FACTOR, 20 / MINIMAP_SCALE_FACTOR);
		mlx->rays[i].data = (int *)mlx_get_data_addr(mlx->rays[i].img_ptr, &(mlx->rays[i].bpp), &(mlx->rays[i].size_l), &(mlx->rays[i].endian));
		y = -1;
		while (++y < 20 / MINIMAP_SCALE_FACTOR)
		{
			x = -1;
			while (++x < 20 / MINIMAP_SCALE_FACTOR)
			{
				mlx->rays[i].data[y * 20 / MINIMAP_SCALE_FACTOR + x] = 0xff0000;
			}
		}
		i++;
	}
}
void put_rays(t_mlx *mlx)
{
	int i = 0;
	float r;

	while (i < NUM_RAYS)
	{
		// r = 0;
		// while (r < mlx->rays[i].distance / MINIMAP_SCALE_FACTOR)
		// {
		// 	mlx_pixel_put(mlx->mlx_ptr, mlx->win, mlx->player.player_x / MINIMAP_SCALE_FACTOR + (r * cos(mlx->rays[i].ray_angle)), mlx->player.player_y / MINIMAP_SCALE_FACTOR + (r * sin(mlx->rays[i].ray_angle)), 0x00FF00);
		// 	r++;
		// }
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->rays[i].img_ptr, mlx->rays[i].wall_hit_x / MINIMAP_SCALE_FACTOR, mlx->rays[i].wall_hit_y / MINIMAP_SCALE_FACTOR);
		i++;
	}
}

void generate_3d_projection(t_mlx *mlx)
{
	int x = 0;
	int i;
	int y;
	while (x < WIN_WIDTH)
	{
		i = x / ceil((double)WIN_WIDTH / (double)NUM_RAYS);
		mlx->window.perp_distance = mlx->rays[i].distance * cos(mlx->rays[i].ray_angle - mlx->player.rotation_angle);
		mlx->window.distance_proj_plane = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
		mlx->window.projected_wall_height = (TILE_SIZE / mlx->window.perp_distance) * mlx->window.distance_proj_plane;
		mlx->window.wall_strip_height = (int)mlx->window.projected_wall_height;
		mlx->window.wall_top_pixel = (WIN_HEIGHT / 2) - (mlx->window.wall_strip_height / 2);
		mlx->window.wall_top_pixel = mlx->window.wall_top_pixel < 0 ? 0 : mlx->window.wall_top_pixel;
		mlx->window.wall_bottom_pixel = (WIN_HEIGHT / 2) + (mlx->window.wall_strip_height / 2);
		mlx->window.wall_bottom_pixel = mlx->window.wall_bottom_pixel > WIN_HEIGHT ? WIN_HEIGHT : mlx->window.wall_bottom_pixel;
		y = 0;
		while (y < mlx->window.wall_top_pixel && y < WIN_HEIGHT)
		{
			mlx->window.data[(WIN_WIDTH * y) + x] = 0x333333;
			y++;
		}
		y = mlx->window.wall_top_pixel;
		while (y < mlx->window.wall_bottom_pixel)
		{
			mlx->window.data[(WIN_WIDTH * y) + x] = mlx->rays[i].was_hit_vertical ? 0xffffff : 0xbbbbbb;
			y++;
		}
		y = mlx->window.wall_bottom_pixel;
		while (y < WIN_HEIGHT && y >= 0)
		{
			mlx->window.data[(WIN_WIDTH * y) + x] = 0x777777;
			y++;
		}
		x++;
	}
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

int rendering_loop(t_mlx *mlx)
{
	move(mlx);
	setting_window(mlx);
	generate_3d_projection(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->window.img_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->map.img_ptr, 0, 0);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->player.img_ptr, mlx->player.player_x / MINIMAP_SCALE_FACTOR, mlx->player.player_y / MINIMAP_SCALE_FACTOR);
	put_line(mlx);
	cast_all_rays(mlx);
	put_rays(mlx);
	return (TRUE);
}

void setting_map(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	mlx->map.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH / MINIMAP_SCALE_FACTOR, WIN_HEIGHT / MINIMAP_SCALE_FACTOR);
	mlx->map.data = (int *)mlx_get_data_addr(mlx->map.img_ptr, &(mlx->map.bpp), &(mlx->map.size_l), &(mlx->map.endian));
	while (++y < WIN_HEIGHT / MINIMAP_SCALE_FACTOR)
	{
		x = -1;
		while (++x < WIN_WIDTH / MINIMAP_SCALE_FACTOR)
		{
			mlx->map.tile_x = x / (TILE_SIZE / MINIMAP_SCALE_FACTOR);
			mlx->map.tile_y = y / (TILE_SIZE / MINIMAP_SCALE_FACTOR);
			if (map[mlx->map.tile_y][mlx->map.tile_x] == 0)
				mlx->map.data[y * WIN_WIDTH / MINIMAP_SCALE_FACTOR + x] = 0x020202;
			else if (map[mlx->map.tile_y][mlx->map.tile_x] == 1)
				mlx->map.data[y * WIN_WIDTH / MINIMAP_SCALE_FACTOR + x] = 0xffffff;
		}
	}
}

void setting_player(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	mlx->player.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->player.width, mlx->player.height);
	mlx->player.data = (int *)mlx_get_data_addr(mlx->player.img_ptr, &(mlx->player.bpp), &(mlx->player.size_l), &(mlx->player.endian));
	while (++y < mlx->player.height)
	{
		x = -1;
		while (++x < mlx->player.width)
		{
			mlx->player.data[y * mlx->player.width + x] = 0xFFFF00;
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

int key_release(int key, t_mlx *mlx)
{
	//	release act
	if (key == KEY_W)
		mlx->player.walk_direction = 0;
	if (key == KEY_S)
		mlx->player.walk_direction = 0;
	if (key == KEY_D)
		mlx->player.side_direction = 0;
	if (key == KEY_A)
		mlx->player.side_direction = 0;
	if (key == KEY_RIGHT)
		mlx->player.turn_direction = 0;
	if (key == KEY_LEFT)
		mlx->player.turn_direction = 0;
	return (TRUE);
}

int		main()
{
	t_mlx	mlx;

	mlx_conf(&mlx);
	if (!(initialize_window(&mlx)))
		return (FALSE);
	setting_map(&mlx);
	setting_player(&mlx);
	setting_ray_point(&mlx);
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &mlx);
	mlx_hook(mlx.win, 17, 1 << 17, &close_button_press, &mlx);
	mlx_hook(mlx.win, X_EVENT_KEY_RELEASE, 1L<<1, &key_release, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &rendering_loop, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (TRUE);
}
