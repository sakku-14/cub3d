#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "../../minilibx_mms_20200219/mlx.h"
#include "../../minilibx_opengl_20191021/mlx.h"
#include "constants.h"

__attribute__((destructor))
void    end()
{
    system("leaks cub3D");
}

int
	error_mes(char *str, int ret)
{
	write(STDERR, str, ft_strlen(str));
	return (ret);
}

void
	free_str_safe(char *str)
{
	free(str);
	str = NULL;
}

int
	free_strs(char **strs, int num, int ret)
{
	while (--num >= 0)
	{
		free_str_safe(strs[num]);
		if (num == 0)
			break ;
	}
	free(strs);
	strs = NULL;
	return (ret);
}

void
	free_mlx_map(t_mlx *mlx)
{
//	free_strs(mlx->conf.map, mlx->conf.map_y, 1);
	int i;

	i = mlx->conf.map_y;
	while (--i >= 0)
	{
		free_str_safe(mlx->conf.map[i]);
		if (i == 0)
			break ;
	}
	free(mlx->conf.map);
	mlx->conf.map = NULL;
}

void
	free_rays(t_mlx *mlx)
{
	free(mlx->rays);
	mlx->rays = NULL;
}

int
	free_mlx(t_mlx *mlx, int ret)
{
	if (mlx->conf.cub_flag[0] == 1)
		free_rays(mlx);
	if (mlx->conf.cub_flag[1])
		free(mlx->conf.path_no);
	if (mlx->conf.cub_flag[2])
		free(mlx->conf.path_so);
	if (mlx->conf.cub_flag[3])
		free(mlx->conf.path_ea);
	if (mlx->conf.cub_flag[4])
		free(mlx->conf.path_we);
	if (mlx->conf.cub_flag[5])
		free(mlx->conf.path_sp);
	if (mlx->conf.cub_flag[8])
		free(mlx->conf.map_str);
	return (ret);
}

float
	dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * ( x1 - x2 ) + (y1 - y2) * (y1 - y2)));
}

void
	mlx_conf(t_mlx *mlx)
{
	mlx->conf.pl_x = (mlx->conf.pl_x + 0.5) * TILE_SIZE;
	mlx->conf.pl_y = (mlx->conf.pl_y + 0.5) * TILE_SIZE;
	mlx->player.width = 4;
	mlx->player.height = 4;
	mlx->player.walk_speed = 3;
	mlx->player.turn_speed = 4 * (PI / 180);
}

int
	map_has_wall_at(t_mlx *mlx, float x, float y)
{
	int map_grid_index_x;
	int map_grid_index_y;
	if (x < 0 || x >= mlx->conf.map_x * TILE_SIZE || y < 0 || y >= mlx->conf.map_y * TILE_SIZE)
		return (TRUE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return ((mlx->conf.map)[map_grid_index_y][map_grid_index_x] == '1');
}

int
	key_press(int key, t_mlx *mlx)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		free_mlx_map(mlx);
		free_mlx(mlx, TRUE);
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

int
	close_button_press(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	free_mlx_map(mlx);
	free_mlx(mlx, TRUE);
	exit(0);
	return (TRUE);
}

void
	put_line(t_mlx *mlx)
{
	int r = 0;
	while (r < 150 / MINIMAP_SCALE_FACTOR)
	{
		mlx_pixel_put(
				mlx->mlx_ptr,
				mlx->win,
				((mlx->conf.pl_x + r * cos(mlx->player.rotation_angle)) * mlx->conf.win_w)
				/ (mlx->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR),
				((mlx->conf.pl_y + r * sin(mlx->player.rotation_angle)) * mlx->conf.win_h)
				/ (mlx->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR),
				0x00FF00
				);
		r++;
	}
}

void
	move(t_mlx *mlx)
{
	float new_player_x = mlx->conf.pl_x;
	float new_player_y = mlx->conf.pl_y;

	if (mlx->player.side_direction == -1)
		new_player_x = mlx->conf.pl_x - cos(mlx->player.rotation_angle + PI / 2) * mlx->player.walk_speed;
	else if (mlx->player.side_direction == 1)
		new_player_x = mlx->conf.pl_x + cos(mlx->player.rotation_angle + PI / 2) * mlx->player.walk_speed;
	else if (mlx->player.walk_direction == 1)
		new_player_y = mlx->conf.pl_y + sin(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (mlx->player.walk_direction == -1)
		new_player_y = mlx->conf.pl_y - sin(mlx->player.rotation_angle) * mlx->player.walk_speed;
	if (mlx->player.side_direction == -1)
		new_player_y = mlx->conf.pl_y - sin(mlx->player.rotation_angle + PI / 2) * mlx->player.walk_speed;
	else if (mlx->player.side_direction == 1)
		new_player_y = mlx->conf.pl_y + sin(mlx->player.rotation_angle + PI / 2) * mlx->player.walk_speed;
	else if (mlx->player.walk_direction == 1)
		new_player_x = mlx->conf.pl_x + cos(mlx->player.rotation_angle) * mlx->player.walk_speed;
	else if (mlx->player.walk_direction == -1)
		new_player_x = mlx->conf.pl_x - cos(mlx->player.rotation_angle) * mlx->player.walk_speed;

	if (mlx->player.turn_direction == 1)
		mlx->player.rotation_angle += 1 * mlx->player.turn_speed;
	else if (mlx->player.turn_direction == -1)
		mlx->player.rotation_angle -= 1 * mlx->player.turn_speed;

	if (!map_has_wall_at(mlx, new_player_x, new_player_y))
	{
		mlx->conf.pl_x = new_player_x;
		mlx->conf.pl_y = new_player_y;
	}
}

float
	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

int
	search_sprite_index(int x, int y, t_mlx *mlx)
{
	int i = 0;
	while (i < mlx->sprite_num)
	{
		if (mlx->sprite[i].sprite_x == x && mlx->sprite[i].sprite_y == y)
			return (i);
		i++;
	}
	return (-1);
}

void
	map_has_sprite_at(float x, float y, t_mlx *mlx)
{
	float	x_to_check;
	float	y_to_check;
	int		index;

	// TODO: ここでエラー処理必要か確認
	if (x < 0 || x >= mlx->conf.map_x * TILE_SIZE || y < 0 || y > mlx->conf.map_y * TILE_SIZE)
		return ;
	x_to_check = floor(x / TILE_SIZE);
	y_to_check = floor(y / TILE_SIZE);
	if (!((int)y_to_check < 0 || (int)x_to_check < 0 || (int)y_to_check >= mlx->conf.map_y || (int)x_to_check >= mlx->conf.map_x))
	{
		if ((mlx->conf.map)[(int)y_to_check][(int)x_to_check] == '2')
		{
			index = search_sprite_index((int)x_to_check, (int)y_to_check, mlx);
			if (index >= 0)
				mlx->sprite[index].visible = 1;
		}
	}
}

void 
	cast_ray(float ray_angle, int strip_id, t_mlx *mlx)
{
	ray_angle = normalize_angle(ray_angle);

	int is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	int is_ray_facing_up = !is_ray_facing_down;
	int is_ray_facing_right = ray_angle < PI / 2 || ray_angle > PI * 3 / 2;
	int is_ray_facing_left = !is_ray_facing_right;

	float x_intercept, y_intercept, x_step, y_step;
	
	///////////////////////////////////////////
	// horizontal ray_grid intersection code
	///////////////////////////////////////////
	int found_horz_wall_hit = FALSE;
	float horz_wall_hit_x = 0;
	float horz_wall_hit_y = 0;
	char horz_wall_content = '\0';

	y_intercept = floor(mlx->conf.pl_y / TILE_SIZE) * TILE_SIZE;
	y_intercept += is_ray_facing_down ? TILE_SIZE : 0;
	x_intercept = mlx->conf.pl_x + (y_intercept - mlx->conf.pl_y) / tan(ray_angle);
	y_step = TILE_SIZE;
	y_step *= is_ray_facing_up ? -1 : 1;
	x_step = TILE_SIZE / tan(ray_angle);
	x_step *= (is_ray_facing_left && x_step > 0) ? -1 : 1;
	x_step *= (is_ray_facing_right && x_step < 0) ? -1 : 1;

	float next_horz_touch_x = x_intercept;
	float next_horz_touch_y = y_intercept;

	while (next_horz_touch_x >= 0 && next_horz_touch_x <= mlx->conf.map_x * TILE_SIZE && next_horz_touch_y >= 0 && next_horz_touch_y <= mlx->conf.map_y * TILE_SIZE)
	{
		float x_to_check = next_horz_touch_x;
		float y_to_check = next_horz_touch_y + (is_ray_facing_up ? -1 : 0);
		map_has_sprite_at(x_to_check, y_to_check, mlx);
		if (map_has_wall_at(mlx, x_to_check, y_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			// TODO: check below
			if (!((int)floor(y_to_check / TILE_SIZE) < 0 || (int)floor(x_to_check / TILE_SIZE) < 0 ||(int)floor(y_to_check / TILE_SIZE) >= mlx->conf.map_y || (int)floor(x_to_check / TILE_SIZE) >= mlx->conf.map_x))
				horz_wall_content = (mlx->conf.map)[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			else
				horz_wall_content = '1';
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
	char vert_wall_content = '\0';

	x_intercept = floor(mlx->conf.pl_x / TILE_SIZE) * TILE_SIZE;
	x_intercept += is_ray_facing_right ? TILE_SIZE : 0;
	y_intercept = mlx->conf.pl_y + (x_intercept - mlx->conf.pl_x) * tan(ray_angle);
	x_step = TILE_SIZE;
	x_step *= is_ray_facing_left ? -1 : 1;
	y_step = TILE_SIZE * tan(ray_angle);
	y_step *= (is_ray_facing_up && y_step > 0) ? -1 : 1;
	y_step *= (is_ray_facing_down && y_step < 0) ? -1 : 1;

	float next_vert_touch_x = x_intercept;
	float next_vert_touch_y = y_intercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= mlx->conf.map_x * TILE_SIZE && next_vert_touch_y >= 0 && next_vert_touch_y <= mlx->conf.map_y * TILE_SIZE)
	{
		float x_to_check = next_vert_touch_x + (is_ray_facing_left ? -1 : 0);
		float y_to_check = next_vert_touch_y;

		map_has_sprite_at(x_to_check, y_to_check, mlx);
		if (map_has_wall_at(mlx, x_to_check, y_to_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			// TODO: check below
//			if ((int)floor(y_to_check / TILE_SIZE) < 0 || (int)floor(x_to_check / TILE_SIZE) < 0 ||(int)floor(y_to_check / TILE_SIZE) >= mlx->conf.map_y || (int)floor(x_to_check / TILE_SIZE) >= mlx->conf.map_x)
//				printf("line 267(vert): y:%d, x:%d\n", (int)floor(y_to_check / TILE_SIZE), (int)floor(x_to_check / TILE_SIZE));
			if (!((int)floor(y_to_check / TILE_SIZE) < 0 || (int)floor(x_to_check / TILE_SIZE) < 0 ||(int)floor(y_to_check / TILE_SIZE) >= mlx->conf.map_y || (int)floor(x_to_check / TILE_SIZE) >= mlx->conf.map_x))
				vert_wall_content = (mlx->conf.map)[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
			else
				vert_wall_content = '1';
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
		? dist_between_points(mlx->conf.pl_x, mlx->conf.pl_y, horz_wall_hit_x, horz_wall_hit_y)
		: FLT_MAX;
	float vert_hit_distance = found_vert_wall_hit
		? dist_between_points(mlx->conf.pl_x, mlx->conf.pl_y, vert_wall_hit_x, vert_wall_hit_y)
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

void
	cast_all_rays(t_mlx *mlx)
{
	int		strip_id;
	float	ray_angle;

	strip_id = 0;
	ray_angle = mlx->player.rotation_angle - (FOV_ANGLE / 2);
	while (strip_id < mlx->conf.win_w)
	{
		cast_ray(ray_angle, strip_id, mlx);
		strip_id++;
		ray_angle += FOV_ANGLE / mlx->conf.win_w;
	}
}

int
	setting_ray_point(t_mlx *mlx)
{
	int x = -1;
	int y = -1;
	int i = 0;

	while (i < mlx->conf.win_w)
	{
		if (!(mlx->rays[i].img_ptr = mlx_new_image(mlx->mlx_ptr, 20 / MINIMAP_SCALE_FACTOR, 20 / MINIMAP_SCALE_FACTOR)))
		{
			free_mlx_map(mlx);
			return (error_mes("Error\n false mlx_new_image for ray image\n", FALSE));
		}
		mlx->rays[i].data = (int *)mlx_get_data_addr(mlx->rays[i].img_ptr, &(mlx->rays[i].bpp), &(mlx->rays[i].size_l), &(mlx->rays[i].endian));
		y = -1;
		while (++y < 20 / MINIMAP_SCALE_FACTOR)
		{
			x = -1;
			while (++x < 20 / MINIMAP_SCALE_FACTOR)
			{
				mlx->rays[i].data[y * (mlx->rays[i].size_l / 4) + x] = 0xff0000;
			}
		}
		i++;
	}
	return (TRUE);
}

void
	put_rays(t_mlx *mlx)
{
	int i = 0;

	while (i < mlx->conf.win_w)
	{
		/*
		r = 0;
		while (r < mlx->rays[i].distance / MINIMAP_SCALE_FACTOR)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win, mlx->conf.pl_x / MINIMAP_SCALE_FACTOR + (r * cos(mlx->rays[i].ray_angle)), mlx->conf.pl_y / MINIMAP_SCALE_FACTOR + (r * sin(mlx->rays[i].ray_angle)), 0x00FF00);
			r++;
		}
		*/
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->rays[i].img_ptr, (mlx->rays[i].wall_hit_x * mlx->conf.win_w) / (mlx->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR), (mlx->rays[i].wall_hit_y * mlx->conf.win_h) / (mlx->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
		i++;
	}
}

void
	get_info_sprite(t_mlx *mlx)
{
	int i = 0;
	float	base;
	float	height;

	while (i < mlx->sprite_num)
	{
		if (mlx->sprite[i].visible == 1)
		{
			base = (mlx->sprite[i].sprite_x + 0.5) * TILE_SIZE - mlx->conf.pl_x;
			height = (mlx->sprite[i].sprite_y + 0.5) * TILE_SIZE - mlx->conf.pl_y;
			mlx->sprite[i].distance = dist_between_points((mlx->sprite[i].sprite_x + 0.5) * TILE_SIZE, (mlx->sprite[i].sprite_y + 0.5) * TILE_SIZE, mlx->conf.pl_x, mlx->conf.pl_y);
			mlx->sprite[i].angle_from_player = atanf(height / base);
			if (base < 0 && height < 0)
				mlx->sprite[i].angle_from_player = PI + mlx->sprite[i].angle_from_player;
			else if (base >= 0 && height < 0)
				mlx->sprite[i].angle_from_player = 2 * PI + mlx->sprite[i].angle_from_player;
			else if (base >= 0 && height >= 0)
				mlx->sprite[i].angle_from_player = mlx->sprite[i].angle_from_player;
			else
				mlx->sprite[i].angle_from_player = PI + mlx->sprite[i].angle_from_player;
		}
		i++;
	}
}

void
	mergesort_sprite_structure(t_mlx *mlx, int left, int right)
{
	int mid, i, j, k;
	t_sprites	tmp[mlx->sprite_num];

	if (left >= right)
		return ;
	mid = (left + right) / 2;
	mergesort_sprite_structure(mlx, left, mid);
	mergesort_sprite_structure(mlx, mid + 1, right);
	i = left;
	while (i <= mid)
	{
		tmp[i] = mlx->sprite[i];
		i++;
	}
	i = mid + 1;
	j = right;
	while (i <= right)
	{
		tmp[i] = mlx->sprite[j];
		i++;
		j--;
	}
	i = left;
	j = right;
	k = left;
	while (k <= right)
	{
		if (tmp[i].distance >= tmp[j].distance)
			mlx->sprite[k] = tmp[i++];
		else
			mlx->sprite[k] = tmp[j--];
		k++;
	}
}

void
	sort_sprite_structure(t_mlx *mlx)
{
	mergesort_sprite_structure(mlx, 0, mlx->sprite_num - 1);
}

void
	generate_3d_projection(t_mlx *mlx)
{
	int x = 0;
	int i;
	int j = 0;
	int y;
	while (x < mlx->conf.win_w)
	{
		i = x / ceil((double)mlx->conf.win_w / (double)mlx->conf.win_w);
		mlx->window.perp_distance = mlx->rays[i].distance * cos(mlx->rays[i].ray_angle - mlx->player.rotation_angle);
		mlx->window.distance_proj_plane = (mlx->conf.win_w / 2) / tan(FOV_ANGLE / 2);
		mlx->window.projected_wall_height = (TILE_SIZE / mlx->window.perp_distance) * mlx->window.distance_proj_plane;
		mlx->window.wall_strip_height = (int)mlx->window.projected_wall_height;
		mlx->window.wall_top_pixel = (mlx->conf.win_h / 2) - (mlx->window.wall_strip_height / 2);
		mlx->window.wall_top_pixel = mlx->window.wall_top_pixel < 0 ? 0 : mlx->window.wall_top_pixel;
		mlx->window.wall_bottom_pixel = (mlx->conf.win_h / 2) + (mlx->window.wall_strip_height / 2);
		mlx->window.wall_bottom_pixel = mlx->window.wall_bottom_pixel > mlx->conf.win_h ? mlx->conf.win_h : mlx->window.wall_bottom_pixel;
		// for sprite
		while (j < mlx->sprite_num)
		{
			if (mlx->sprite[j].visible == 1)
			{
				mlx->sprite[j].perp_distance = mlx->sprite[j].distance * cos(mlx->sprite[j].angle_from_player - mlx->player.rotation_angle);
				mlx->sprite[j].distance_proj_plane = (mlx->conf.win_w / 2) / tan(FOV_ANGLE / 2);
				mlx->sprite[j].projected_sprite_height = (TILE_SIZE / mlx->sprite[j].perp_distance) * mlx->sprite[j].distance_proj_plane;
				mlx->sprite[j].sprite_strip_height = (int)mlx->sprite[j].projected_sprite_height;
				mlx->sprite[j].sprite_top_pixel = (mlx->conf.win_h / 2) - (mlx->sprite[j].sprite_strip_height / 2);
				mlx->sprite[j].sprite_top_pixel = mlx->sprite[j].sprite_top_pixel < 0 ? 0 : mlx->sprite[j].sprite_top_pixel;
				mlx->sprite[j].sprite_bottom_pixel = (mlx->conf.win_h / 2) + (mlx->sprite[j].sprite_strip_height / 2);
				mlx->sprite[j].sprite_bottom_pixel = mlx->sprite[j].sprite_bottom_pixel > mlx->conf.win_h ? mlx->conf.win_h : mlx->sprite[j].sprite_bottom_pixel;
			}
			j++;
		}
		// describe about ceil
		y = 0;
		while (y < mlx->window.wall_top_pixel && y < mlx->conf.win_h)
		{
			mlx->window.data[((mlx->window.size_l / 4) * y) + x] = mlx->conf.ceil_c;
			y++;
		}
		// describe about wall(texture)
		if (mlx->rays[i].was_hit_vertical)
			mlx->window.texture_offset_x = (int)mlx->rays[i].wall_hit_y % TEXTURE_HEIGHT;
		else
			mlx->window.texture_offset_x = (int)mlx->rays[i].wall_hit_x % TEXTURE_WIDTH;
		y = mlx->window.wall_top_pixel;
		while (y < mlx->window.wall_bottom_pixel)
		{
			int tex_index;
			if (mlx->rays[i].was_hit_vertical)
				tex_index = mlx->rays[i].is_ray_facing_right ? 2 : 3;
			else
				tex_index = mlx->rays[i].is_ray_facing_up ? 0 : 1;
			mlx->window.distance_from_top = y + (mlx->window.wall_strip_height / 2) - (mlx->conf.win_h / 2);
			mlx->window.texture_offset_y = mlx->window.distance_from_top * ((float)64 / mlx->window.wall_strip_height);
			if (tex_index == 0 || tex_index == 2)
				mlx->window.data[((mlx->window.size_l / 4) * y) + x] = mlx->tex[tex_index].data[((mlx->tex[tex_index].size_l / 4) * mlx->window.texture_offset_y) + mlx->window.texture_offset_x];
			else
			{
				mlx->window.texture_offset_x_rev = TEXTURE_WIDTH - mlx->window.texture_offset_x - 1;
				mlx->window.data[((mlx->window.size_l / 4) * y) + x] = mlx->tex[tex_index].data[((mlx->tex[tex_index].size_l / 4) * mlx->window.texture_offset_y) + mlx->window.texture_offset_x_rev];
			}
			y++;
		}
		// describe about floor
		y = mlx->window.wall_bottom_pixel;
		while (y < mlx->conf.win_h && y >= 0)
		{
			mlx->window.data[((mlx->window.size_l / 4) * y) + x] = mlx->conf.floor_c;
			y++;
		}
		// describe about sprite
		j = 0;
		while (j < mlx->sprite_num)
		{
			if (mlx->sprite[j].distance < mlx->rays[i].distance && mlx->sprite[j].visible == 1 && x >= ((normalize_angle((mlx->sprite[j].angle_from_player - mlx->player.rotation_angle) + (FOV_ANGLE / 2)) / FOV_ANGLE) * mlx->conf.win_w) - (mlx->sprite[j].projected_sprite_height / 2) && x <= ((normalize_angle((mlx->sprite[j].angle_from_player - mlx->player.rotation_angle) + (FOV_ANGLE / 2)) / FOV_ANGLE) * mlx->conf.win_w) + (mlx->sprite[j].projected_sprite_height / 2))
			{
				mlx->sprite[j].texture_offset_x = (int)((x - (((normalize_angle((mlx->sprite[j].angle_from_player - mlx->player.rotation_angle) + (FOV_ANGLE / 2)) / FOV_ANGLE) * mlx->conf.win_w) - (mlx->sprite[j].projected_sprite_height / 2))) / mlx->sprite[j].projected_sprite_height * TEXTURE_WIDTH); 
				y = mlx->sprite[j].sprite_top_pixel;
				while (y < mlx->sprite[j].sprite_bottom_pixel)
				{
					mlx->sprite[j].distance_from_top = y + (mlx->sprite[j].sprite_strip_height / 2) - (mlx->conf.win_h / 2);
					mlx->sprite[j].texture_offset_y = mlx->sprite[j].distance_from_top * ((float)64 / mlx->sprite[j].sprite_strip_height);
					if ((mlx->tex[4].data[((mlx->tex[4].size_l / 4) * mlx->sprite[j].texture_offset_y) + mlx->sprite[j].texture_offset_x] & 0xffffff) != 0 )
					{
						mlx->window.data[((mlx->window.size_l / 4) * y) + x] = mlx->tex[4].data[((mlx->tex[4].size_l / 4) * mlx->sprite[j].texture_offset_y) + mlx->sprite[j].texture_offset_x];
					}
					y++;
				}
			}
			j++;
		}
		x++;
	}
}

int
	setting_window(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	if (!(mlx->window.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->conf.win_w, mlx->conf.win_h)))
	{
		free_mlx_map(mlx);
		return (FALSE);
	}
	mlx->window.data = (int *)mlx_get_data_addr(mlx->window.img_ptr, &(mlx->window.bpp), &(mlx->window.size_l), &(mlx->window.endian));
	while (++y < mlx->conf.win_h)
	{
		x = -1;
		while (++x < mlx->conf.win_w)
		{
			mlx->window.data[y * (mlx->window.size_l / 4) + x] = 0x000000;
		}
	}
	return (TRUE);
}

void
	reset_sprite_info(t_mlx *mlx)
{
	int i = 0;
	while (i < mlx->sprite_num)
	{
		mlx->sprite[i].visible = 0;
		mlx->sprite[i].distance = 0;
		i++;
	}
}

int
	rendering_loop(t_mlx *mlx)
{
	move(mlx);
	cast_all_rays(mlx);
	get_info_sprite(mlx);
	sort_sprite_structure(mlx);
	generate_3d_projection(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->window.img_ptr, 0, 0);
//	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->map.img_ptr, 0, 0);
//	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->player.img_ptr, (mlx->conf.pl_x * mlx->conf.win_w) / (mlx->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR), (mlx->conf.pl_y * mlx->conf.win_h) / (mlx->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
//	put_line(mlx);
//	put_rays(mlx);
	reset_sprite_info(mlx);
	return (TRUE);
}

int
	rendering_for_bmp(t_mlx *mlx)
{
	move(mlx);
	cast_all_rays(mlx);
	get_info_sprite(mlx);
	sort_sprite_structure(mlx);
	generate_3d_projection(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->window.img_ptr, 0, 0);
//	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->map.img_ptr, 0, 0);
//	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->player.img_ptr, (mlx->conf.pl_x * mlx->conf.win_w) / (mlx->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR), (mlx->conf.pl_y * mlx->conf.win_h) / (mlx->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
//	put_line(mlx);
//	put_rays(mlx);
//	reset_sprite_info(mlx);
	return (TRUE);
}

int
	setting_map(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	//TODO: leak check again
	if(!(mlx->map.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->conf.win_w / MINIMAP_SCALE_FACTOR, mlx->conf.win_h / MINIMAP_SCALE_FACTOR)))
	{
		free_mlx_map(mlx);
		return (error_mes("Error\n false mlx_new_image for map image\n", FALSE));
	}
	mlx->map.data = (int *)mlx_get_data_addr(mlx->map.img_ptr, &(mlx->map.bpp), &(mlx->map.size_l), &(mlx->map.endian));
	while (++y < mlx->conf.win_h / MINIMAP_SCALE_FACTOR)
	{
		x = -1;
		while (++x < mlx->conf.win_w / MINIMAP_SCALE_FACTOR)
		{
			mlx->map.tile_x = (x * mlx->conf.map_x) / (mlx->conf.win_w / MINIMAP_SCALE_FACTOR);
			mlx->map.tile_y = (y * mlx->conf.map_y) / (mlx->conf.win_h / MINIMAP_SCALE_FACTOR);
			if ((mlx->conf.map)[mlx->map.tile_y][mlx->map.tile_x] == '0')
				mlx->map.data[y * (mlx->map.size_l / 4) + x] = 0x020202;
			else if ((mlx->conf.map)[mlx->map.tile_y][mlx->map.tile_x] == '1')
				mlx->map.data[y * (mlx->map.size_l / 4) + x] = 0xffffff;
		}
	}
	return (TRUE);
}

int
	setting_player(t_mlx *mlx)
{
	int x = -1;
	int y = -1;

	//TODO: leak check again
	if (!(mlx->player.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->player.width, mlx->player.height)))
	{
		free_mlx_map(mlx);
		return (error_mes("Error\n false mlx_new_image for player image\n", FALSE));
	}
	mlx->player.data = (int *)mlx_get_data_addr(mlx->player.img_ptr, &(mlx->player.bpp), &(mlx->player.size_l), &(mlx->player.endian));
	while (++y < mlx->player.height)
	{
		x = -1;
		while (++x < mlx->player.width)
		{
			mlx->player.data[y * (mlx->player.size_l / 4) + x] = 0xFFFF00;
		}
	}
	return (TRUE);
}

int
	check_path_available(t_mlx *mlx)
{
	int fd[5];
	int i;

	fd[0] = open(mlx->conf.path_no, O_RDONLY);
	close(fd[0]);
	fd[1] = open(mlx->conf.path_so, O_RDONLY);
	close(fd[1]);
	fd[2] = open(mlx->conf.path_ea, O_RDONLY);
	close(fd[2]);
	fd[3] = open(mlx->conf.path_we, O_RDONLY);
	close(fd[3]);
	fd[4] = open(mlx->conf.path_sp, O_RDONLY);
	close(fd[4]);
	i = 0;
	while (i < 5)
	{
		if (fd[i] == -1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int
	free_map_ret_error(t_mlx *mlx, char *str, int ret)
{
	free_mlx_map(mlx);
	error_mes(str, ret);
	return (ret);
}

int
	setting_img(t_mlx *mlx)
{
	int width = TEXTURE_WIDTH;
	int height = TEXTURE_HEIGHT;

	if (!check_path_available(mlx))
		return (free_map_ret_error(mlx, "Error\n invalid path of texture\n", FALSE));
	if (!(mlx->tex[0].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->conf.path_no, &width, &height)))
		return (free_map_ret_error(mlx,"Error\n invalid texture file\n" , FALSE));
	mlx->tex[0].data = (int *)mlx_get_data_addr(mlx->tex[0].img_ptr, &(mlx->tex[0].bpp), &(mlx->tex[0].size_l), &(mlx->tex[0].endian));
	if (!(mlx->tex[1].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->conf.path_so, &width, &height)))
		return (free_map_ret_error(mlx,"Error\n invalid texture file\n" , FALSE));
	mlx->tex[1].data = (int *)mlx_get_data_addr(mlx->tex[1].img_ptr, &(mlx->tex[1].bpp), &(mlx->tex[1].size_l), &(mlx->tex[1].endian));
	if (!(mlx->tex[2].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->conf.path_ea, &width, &height)))
		return (free_map_ret_error(mlx,"Error\n invalid texture file\n" , FALSE));
	mlx->tex[2].data = (int *)mlx_get_data_addr(mlx->tex[2].img_ptr, &(mlx->tex[2].bpp), &(mlx->tex[2].size_l), &(mlx->tex[2].endian));
	if (!(mlx->tex[3].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->conf.path_we, &width, &height)))
		return (free_map_ret_error(mlx,"Error\n invalid texture file\n" , FALSE));
	mlx->tex[3].data = (int *)mlx_get_data_addr(mlx->tex[3].img_ptr, &(mlx->tex[3].bpp), &(mlx->tex[3].size_l), &(mlx->tex[3].endian));
	if (!(mlx->tex[4].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, mlx->conf.path_sp, &width, &height)))
		return (free_map_ret_error(mlx,"Error\n invalid texture file\n" , FALSE));
	mlx->tex[4].data = (int *)mlx_get_data_addr(mlx->tex[4].img_ptr, &(mlx->tex[4].bpp), &(mlx->tex[4].size_l), &(mlx->tex[4].endian));
	return (TRUE);
}

void
	check_sprite_info(t_mlx *mlx)
{
	int i, j, k;

	mlx->sprite_num = 0;
	i = 0;
	j = 0;
	while (i < mlx->conf.map_y)
	{
		j = 0;
		while (j < mlx->conf.map_x)
		{
			if ((mlx->conf.map)[i][j] == '2')
				mlx->sprite_num++;
			j++;
		}
		i++;
	}
	mlx->sprite = malloc(sizeof(t_sprites) * (mlx->sprite_num + 1));
	i = 0;
	k = 0;
	while (i < mlx->conf.map_y)
	{
		j = 0;
		while (j < mlx->conf.map_x && k < mlx->sprite_num)
		{
			if ((mlx->conf.map)[i][j] == '2')
			{
				mlx->sprite[k].sprite_y = i;
				mlx->sprite[k].sprite_x = j;
				mlx->sprite[k].visible = 0;
				k++;
			}
			j++;
		}
		i++;
	}
	mlx->sprite[k].sprite_x =  -1;
	mlx->sprite[k].sprite_y = -1;
	mlx->sprite[k].visible = -1;
}

int
	initialize_window(t_mlx *mlx)
{
	if (!(mlx->mlx_ptr = mlx_init()))
		return (FALSE);
	if (!(mlx->win = mlx_new_window(mlx->mlx_ptr, mlx->conf.win_w, mlx->conf.win_h, "cub3d_window")))
		return (FALSE);
	return (TRUE);
}

int
	key_release(int key, t_mlx *mlx)
{
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

int
	get_ray_size(t_mlx *mlx)
{
	if (!(mlx->rays = malloc(sizeof(t_rays) * (mlx->conf.win_w + 1))))
		return (FALSE);
	return (TRUE);
}

int
	is_all_digit(char *str)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int
	pack_win_size(t_mlx *mlx, char *line)
{
	char	**strs;
	int		num;

	strs = ft_split(line, ' ');
	num = 0;
	while (strs[num])
		num++;
	if (num != 3)
		return (free_strs(strs, num, FALSE));
	if (ft_strlen(strs[0]) != 1)
		return (free_strs(strs, num, FALSE));
	if (!is_all_digit(strs[1]) || !is_all_digit(strs[2]))
		return (free_strs(strs, num, FALSE));
	mlx->conf.win_w = ft_atoi(strs[1]);
	mlx->conf.win_h = ft_atoi(strs[2]);
	if (mlx->conf.win_w <= 0 || mlx->conf.win_h <= 0)
		return (free_strs(strs, num, FALSE));
	mlx->conf.win_w = mlx->conf.win_w > mlx->conf.win_max_w ? mlx->conf.win_max_w : mlx->conf.win_w;
	mlx->conf.win_h = mlx->conf.win_h > mlx->conf.win_max_h ? mlx->conf.win_max_h : mlx->conf.win_h;
	if (get_ray_size(mlx) == FALSE)
		return (free_strs(strs, num, FALSE));
	free_str_safe(line);
	return (free_strs(strs, num, TRUE));
}

int
	pack_path(t_mlx *mlx, char *line)
{
	char	**strs;
	int		num;
	int		len;

	strs = ft_split(line, ' ');
	num = 0;
	while (strs[num])
		num++;
	if (num != 2)
		return (free_strs(strs, num, FALSE));
	if (ft_strlen(strs[0]) != 2 \
			&& (ft_strlen(strs[0]) != 1 && ft_strncmp(strs[0], "S", 1)))
		return (free_strs(strs, num, FALSE));
	len = ft_strlen(strs[1]);
	if (strs[1])
	{
		if (ft_strnstr(strs[0], "NO", 2))
			mlx->conf.path_no = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "SO", 2))
			mlx->conf.path_so = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "EA", 2))
			mlx->conf.path_ea = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "WE", 2))
			mlx->conf.path_we = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "S", 1))
			mlx->conf.path_sp = ft_substr(strs[1], 0, len);
	}
	free_str_safe(line);
	return (free_strs(strs, num, TRUE));
}

int
	check_rgb_available(char **strs, t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (strs[i][j] != '\0')
		{
			if (ft_isdigit(strs[i][j]))
				j++;
			else
				return (FALSE);
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (mlx->conf.floor_colors[i] < 0 || mlx->conf.floor_colors[i] > 255)
			return (FALSE);
		if (mlx->conf.ceil_colors[i] < 0 || mlx->conf.ceil_colors[i] > 255)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int
	pack_rgb(t_mlx *mlx, char *line)
{
	char	**sub_strs;
	char	**strs;
	int		num;

	sub_strs = ft_split(line, ' ');
	num = 0;
	while (sub_strs[num])
		num++;
	if (num != 2)
		return (free_strs(sub_strs, num, FALSE));
	strs = ft_split(sub_strs[1], ',');
	num = 0;
	while (strs[num])
		num++;
	if (num != 3)
	{
		free_strs(sub_strs, 2, 0);
		return (free_strs(strs, num, FALSE));
	}
	if (ft_strnstr(sub_strs[0], "F", 1) && ft_strlen(sub_strs[0]) == 1)
	{
		mlx->conf.floor_colors[0] = ft_atoi(strs[0]);
		mlx->conf.floor_colors[1] = ft_atoi(strs[1]);
		mlx->conf.floor_colors[2] = ft_atoi(strs[2]);
	}
	else if (ft_strnstr(sub_strs[0], "C", 1) && ft_strlen(sub_strs[0]) == 1)
	{
		mlx->conf.ceil_colors[0] = ft_atoi(strs[0]);
		mlx->conf.ceil_colors[1] = ft_atoi(strs[1]);
		mlx->conf.ceil_colors[2] = ft_atoi(strs[2]);
	}
	else
	{
		free_strs(sub_strs, 2, 0);
		return (free_strs(strs, num, FALSE));
	}
	if (!check_rgb_available(strs, mlx))
	{
		free_strs(sub_strs, 2, 0);
		return (free_strs(strs, num, FALSE));
	}
	mlx->conf.floor_c = mlx->conf.floor_colors[0];
	mlx->conf.floor_c = mlx->conf.floor_c << 8;
	mlx->conf.floor_c = mlx->conf.floor_c | mlx->conf.floor_colors[1];
	mlx->conf.floor_c = mlx->conf.floor_c << 8;
	mlx->conf.floor_c = mlx->conf.floor_c | mlx->conf.floor_colors[2];
	mlx->conf.ceil_c = mlx->conf.ceil_colors[0];
	mlx->conf.ceil_c = mlx->conf.ceil_c << 8;
	mlx->conf.ceil_c = mlx->conf.ceil_c | mlx->conf.ceil_colors[1];
	mlx->conf.ceil_c = mlx->conf.ceil_c << 8;
	mlx->conf.ceil_c = mlx->conf.ceil_c | mlx->conf.ceil_colors[2];
	free_strs(sub_strs, 2, 0);
	free_str_safe(line);
	return (free_strs(strs, num, TRUE));
}

int
	max_len(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}

int
	pack_map_str(t_mlx *mlx, char *line)
{
	char *tmp;
	int len;

	if (mlx->conf.cub_flag[8] == 1)
	{
		if (!(mlx->conf.map_str = malloc(sizeof(char))))
			return (error_mes("Error\n could not malloc for map_str\n", FALSE));
		*(mlx->conf.map_str) = '\0';
	}
	mlx->conf.cub_flag[8]++;
	len = ft_strlen(line);
	mlx->conf.map_x = max_len(mlx->conf.map_x, len);
	tmp = mlx->conf.map_str;
	mlx->conf.map_str = ft_strjoin(mlx->conf.map_str, line);
	free_str_safe(tmp);
	tmp = mlx->conf.map_str;
	mlx->conf.map_str = ft_strjoin(mlx->conf.map_str, "\n");
	mlx->conf.map_y++;
	free_str_safe(tmp);
	return (TRUE);
}

int
	conf_fill_checker(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (mlx->conf.cub_flag[i++] == 0)
			return (FALSE);
	}
	return (TRUE);
}

int
	check_c_in_str(char c, char *str)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int
	check_is_map(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!check_c_in_str(line[i], " 012NSEW"))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int
	get_conf(t_mlx *mlx, char *file_name)
{
	int fd;
	int res;
	int flag;
	char *line;
	char *tmp;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (error_mes("Error\n invalid fd\n", FALSE));
	flag = 0;
	mlx->conf.map_y = 0;
	mlx->conf.map_x = 0;
	while ((res = get_next_line(fd, &line)))
	{
		if (res == -1)
			return (error_mes("Error\n some error while gnl working\n", FALSE));
		if (!*line)
		{
			free_str_safe(line);
			if (flag == 9)
				flag = 10;
		}
		else if (flag >= 8)
		{
			if ((mlx->conf.cub_flag[8] == 0 && conf_fill_checker(mlx) == FALSE) || flag == 10)
			{
				free_str_safe(line);
				return (error_mes("ERROR: invalid configure\n", FALSE));
			}
			if (check_is_map(line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n map is not made by map element\n", FALSE));
			}
			flag = 9;
			mlx->conf.cub_flag[8]++;
			if (pack_map_str(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (FALSE);
			}
			free_str_safe(line);
		}
		else if (ft_strnstr(line, "R", 1))
		{
			if (pack_win_size(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n invalid configure\n", FALSE));
			}
			flag++;
			mlx->conf.cub_flag[0] = 1;
		}
		else if (ft_strnstr(line, "NO", 2))
		{
			if (pack_path(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n invalid configure\n", FALSE));
			}
			flag++;
			mlx->conf.cub_flag[1] = 1;
		}
		else if (ft_strnstr(line, "SO", 2))
		{
			if (pack_path(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n invalid configure\n", FALSE));
			}
			flag++;
			mlx->conf.cub_flag[2] = 1;
		}
		else if (ft_strnstr(line, "EA", 2))
		{
			if (pack_path(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n invalid configure\n", FALSE));
			}
			flag++;
			mlx->conf.cub_flag[3] = 1;
		}
		else if (ft_strnstr(line, "WE", 2))
		{
			if (pack_path(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n invalid configure\n", FALSE));
			}
			flag++;
			mlx->conf.cub_flag[4] = 1;
		}
		else if (ft_strnstr(line, "S", 1))
		{
			if (pack_path(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n invalid configure\n", FALSE));
			}
			flag++;
			mlx->conf.cub_flag[5] = 1;
		}
		else if (ft_strnstr(line, "F", 1))
		{
			if (pack_rgb(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n invalid configure\n", FALSE));
			}
			flag++;
			mlx->conf.cub_flag[6] = 1;
		}
		else if (ft_strnstr(line, "C", 1))
		{
			if (pack_rgb(mlx, line) == FALSE)
			{
				free_str_safe(line);
				return (error_mes("Error\n invalid configure\n", FALSE));
			}
			flag++;
			mlx->conf.cub_flag[7] = 1;
		}
		else
		{
			free_str_safe(line);
			return (error_mes("Error\n invalid configure\n", FALSE));
		}
	}
	mlx->conf.map = ft_split(mlx->conf.map_str, '\n');
	int index = 0;
	// mapの幅を空白で埋める
	while (index < mlx->conf.map_y)
	{
		while ((int)ft_strlen((mlx->conf.map)[index]) < mlx->conf.map_x)
		{
			tmp = mlx->conf.map[index];
			(mlx->conf.map)[index] = ft_strjoin((mlx->conf.map)[index], " ");
			free_str_safe(tmp);
		}
		index++;
	}
	free_str_safe(line);
	return (TRUE);
}

void
	print_map(char *map_p, int y, int x)
{
	int i = 0;
	int j = 0;

	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%c", map_p[i * x + j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void
	check_fill(char *map_p, int y, int x, int p_y, int p_x, int *false_checker)
{
	if (map_p[p_y * x + p_x] == 'p' || map_p[p_y * x + p_x] == '1' || map_p[p_y * x + p_x] == '3' || *false_checker == 1)
		return ;
	if (map_p[p_y * x + p_x] == 'X')
	{
		*false_checker = 1;
		return ;
	}
	if (map_p[p_y * x + p_x] == '0' || map_p[p_y * x + p_x] == 's')
		map_p[p_y * x + p_x] = 'p';
	if (map_p[p_y * x + p_x] == '2')
		map_p[p_y * x + p_x] = '3';
	check_fill(map_p, y, x, p_y - 1, p_x, false_checker);
	check_fill(map_p, y, x, p_y, p_x + 1, false_checker);
	check_fill(map_p, y, x, p_y + 1, p_x, false_checker);
	check_fill(map_p, y, x, p_y, p_x - 1, false_checker);
}

void
	put_grid_to_container(t_mlx *mlx, char *cont_p, int y, int x)
{
	int i = 0, j = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (i == 0 || i == y - 1 || j == 0 || j == x - 1)
				cont_p[i * x + j] = 'X';
			else if (i > y - 2 || j > x - 2 || (mlx->conf.map)[i - 1][j - 1] == ' ')
				cont_p[i * x + j] = 's';
			else
				cont_p[i * x + j] = (mlx->conf.map)[i - 1][j - 1];
			j++;
		}
		i++;
	}
}

int
	pick_player_pl(char *cont_p, int y, int x, int *player_y, int *player_x, t_mlx *mlx)
{
	int i = 0, j = 0;
	int player_counter = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (cont_p[i * x + j] == 'N' || cont_p[i * x + j] == 'S' || cont_p[i * x + j] == 'E' || cont_p[i * x + j] == 'W')
			{
				if (cont_p[i * x + j] == 'N')
					mlx->player.rotation_angle = 270 * (PI / 180);
				else if (cont_p[i * x + j] == 'S')
					mlx->player.rotation_angle = 90 * (PI / 180);
				else if (cont_p[i * x + j] == 'E')
					mlx->player.rotation_angle = 0 * (PI / 180);
				else if (cont_p[i * x + j] == 'W')
					mlx->player.rotation_angle = 180 * (PI / 180);
				*player_y = i;
				*player_x = j;
				player_counter++;
			}
			j++;
		}
		i++;
	}
	if (player_counter == 1)
		return (TRUE);
	free_str_safe(cont_p);
	return (FALSE);
}

int
	check_map(t_mlx *mlx)
{
	int player_x, player_y;
	int y = mlx->conf.map_y + 2;
	int x = mlx->conf.map_x + 2;
	char *cont_p = malloc(sizeof(char) * y * x);
	int false_checker = -1;

	put_grid_to_container(mlx, cont_p, y, x);
//	printf("\n***origin map packed in container***\n");
//	print_map(cont_p, y, x);
	if (!pick_player_pl(cont_p, y, x, &player_y, &player_x, mlx))
	{
		free_mlx_map(mlx);
		return (error_mes("Error\n Player does not exist or more than 2 players on the map\n", FALSE));
	}
//	printf("\nplayer position:(%d, %d)\n\n", player_y, player_x);
//	printf("\nmap scale:(%d, %d)\n\n", mlx->conf.map_y, mlx->conf.map_x);
	check_fill(cont_p, y, x, player_y, player_x, &false_checker);
//	printf("***map filled by p***\n");
//	print_map(cont_p, y, x);
	if (false_checker == 1)
	{
		free_mlx_map(mlx);
		free_str_safe(cont_p);
		return (error_mes("Error\n Map is not sorrounded by wall.\n", FALSE));
	}
	mlx->conf.pl_y = player_y - 1;
	mlx->conf.pl_x = player_x - 1;
	free_str_safe(cont_p);
	return (TRUE);
}

int
	cub_checker(char *av)
{
	int i;

	i = 0;
	if (!av || !av[i])
		return (FALSE);
	while (av[i])
	{
		if (av[i] == '.')
		{
			if (!(ft_strncmp(&av[i], ".cub", 4)) && (ft_strlen(&av[i]) == 4))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int
	save_checker(char *av)
{
	if (av && *av)
	{
		if (ft_strncmp(av, "--save", 6) || !(ft_strlen(av) == 6))
			return (FALSE);
	}
	return (TRUE);
}

void
	init_vars(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 9)
		ft_bzero(&(mlx->conf.cub_flag[i++]), sizeof(int));
}

void
	make_img(t_mlx *mlx, int fd)
{
	int	x;
	int	y;
	int	color;

	y = mlx->conf.win_h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < mlx->conf.win_w)
		{
			color = mlx->window.data[((mlx->window.size_l / 4) * y) + x];
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

void
	make_header(t_mlx *mlx, int fd, unsigned int header_size, unsigned int img_size)
{
	unsigned int	file_header_size;
	unsigned int	info_header_size;
	unsigned int	bmp_size;
	unsigned int	plane;

	file_header_size = write(fd, "BM", 2);
	bmp_size = header_size + img_size;
	file_header_size += write(fd, &bmp_size, 4);
	file_header_size += write(fd, "\0\0\0\0", 4);
	file_header_size += write(fd, &header_size, 4);
	info_header_size = header_size - file_header_size;
	write(fd, &info_header_size, 4);
	write(fd, &(mlx->conf.win_w), 4);
	write(fd, &(mlx->conf.win_h), 4);
	plane = 1;
	write(fd, &plane, 2);
	write(fd, &(mlx->window.bpp), 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &img_size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

int
	create_bmp(t_mlx *mlx)
{
	int	fd;
	unsigned int	img_size;
	unsigned int	header_size;

	rendering_for_bmp(mlx);
	if ((fd = open("image.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
	{
		close(fd);
		free_mlx_map(mlx);
		return (FALSE);
	}
	img_size = (unsigned int)(mlx->conf.win_w * mlx->conf.win_h) * (mlx->window.bpp / 8);
	header_size = 54;
	make_header(mlx, fd, header_size, img_size);
	make_img(mlx, fd);
	free_mlx_map(mlx);
	free_mlx(mlx, TRUE);
	exit (0);
}

int
	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac <= 1 || ac > 3)
		return (error_mes("Error\n few args or too many args\n", ERROR));
	if ((ac == 3 && !save_checker(av[2])) || (ac == 3 && !save_checker(av[2])))
		return (error_mes("Error\n invalid args\n", ERROR));
	init_vars(&mlx);
	mlx_get_screen_size(mlx.mlx_ptr, &(mlx.conf.win_max_w), &(mlx.conf.win_max_h));
	if (get_conf(&mlx, av[1]) == FALSE)
		return (free_mlx(&mlx, ERROR));
	if (check_map(&mlx) == FALSE)
		return (free_mlx(&mlx, ERROR));
	mlx_conf(&mlx);
	if (!(initialize_window(&mlx)) || setting_img(&mlx) == FALSE \
		|| setting_window(&mlx) == FALSE)
		return (free_mlx(&mlx, ERROR));
/*
//	if (setting_map(&mlx) == FALSE)
//		return (free_mlx(&mlx, ERROR));
//	if (setting_player(&mlx) == FALSE)
//		return (free_mlx(&mlx, ERROR));
//	if (setting_ray_point(&mlx) == FALSE)
//		return (free_mlx(&mlx, ERROR));
*/
	check_sprite_info(&mlx);
	if (ac == 3 && create_bmp(&mlx) == FALSE)
		return (free_mlx(&mlx, ERROR));
	mlx_hook(mlx.win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &mlx);
	mlx_hook(mlx.win, 17, 1 << 17, &close_button_press, &mlx);
	mlx_hook(mlx.win, X_EVENT_KEY_RELEASE, 1L<<1, &key_release, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, &rendering_loop, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (TRUE);
}
