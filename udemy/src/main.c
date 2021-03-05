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
	free_cub_map(t_cub *cub)
{
	int i;

	i = cub->conf.map_y;
	while (--i >= 0)
	{
		free_str_safe(cub->conf.map[i]);
		if (i == 0)
			break ;
	}
	free(cub->conf.map);
	cub->conf.map = NULL;
}

void
	free_rays(t_cub *cub)
{
	free(cub->rays);
	cub->rays = NULL;
}

int
	free_cub(t_cub *cub, int ret)
{
	if (cub->conf.cub_flag[0] == 1)
		free_rays(cub);
	if (cub->conf.cub_flag[1])
		free(cub->conf.path_no);
	if (cub->conf.cub_flag[2])
		free(cub->conf.path_so);
	if (cub->conf.cub_flag[3])
		free(cub->conf.path_ea);
	if (cub->conf.cub_flag[4])
		free(cub->conf.path_we);
	if (cub->conf.cub_flag[5])
		free(cub->conf.path_sp);
	if (cub->conf.cub_flag[8])
		free(cub->conf.map_str);
	return (ret);
}

float
	dist_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt((x1 - x2) * ( x1 - x2 ) + (y1 - y2) * (y1 - y2)));
}

void
	cub_conf(t_cub *cub)
{
	cub->conf.pl_x = (cub->conf.pl_x + 0.5) * TILE_SIZE;
	cub->conf.pl_y = (cub->conf.pl_y + 0.5) * TILE_SIZE;
	cub->player.width = 4;
	cub->player.height = 4;
	cub->player.walk_speed = 3;
	cub->player.turn_speed = 4 * (PI / 180);
}

int
	map_has_wall_at(t_cub *cub, float x, float y)
{
	int map_grid_index_x;
	int map_grid_index_y;
	if (x < 0 || x >= cub->conf.map_x * TILE_SIZE \
			|| y < 0 || y >= cub->conf.map_y * TILE_SIZE)
		return (TRUE);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	return ((cub->conf.map)[map_grid_index_y][map_grid_index_x] == '1');
}

int
	key_press(int key, t_cub *cub)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(cub->cub_ptr, cub->win);
		free_cub_map(cub);
		free_cub(cub, TRUE);
		exit(0);
	}
	if (key == KEY_W)
		cub->player.walk_direction = +1;
	if (key == KEY_S)
		cub->player.walk_direction = -1;
	if (key == KEY_D)
		cub->player.side_direction = +1;
	if (key == KEY_A)
		cub->player.side_direction = -1;
	if (key == KEY_RIGHT)
		cub->player.turn_direction = +1;
	if (key == KEY_LEFT)
		cub->player.turn_direction = -1;
	return (TRUE);
}

int
	close_button_press(t_cub *cub)
{
	mlx_destroy_window(cub->cub_ptr, cub->win);
	free_cub_map(cub);
	free_cub(cub, TRUE);
	exit(0);
	return (TRUE);
}

/*
void
	put_line(t_cub *cub)
{
	int r = 0;
	while (r < 150 / MINIMAP_SCALE_FACTOR)
	{
		mlx_pixel_put(
				cub->cub_ptr,
				cub->win,
				((cub->conf.pl_x + r * cos(cub->player.rotation_angle)) * cub->conf.win_w)
				/ (cub->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR),
				((cub->conf.pl_y + r * sin(cub->player.rotation_angle)) * cub->conf.win_h)
				/ (cub->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR),
				0x00FF00
				);
		r++;
	}
}
*/

void
	set_new_player_x(t_cub *cub, float *new_player_x)
{
	if (cub->player.side_direction == 1)
		*new_player_x = cub->conf.pl_x \
			+ cos(cub->player.rotation_angle + PI / 2) * cub->player.walk_speed;
	else if (cub->player.side_direction == -1)
		*new_player_x = cub->conf.pl_x \
			- cos(cub->player.rotation_angle + PI / 2) * cub->player.walk_speed;
	else if (cub->player.walk_direction == 1)
		*new_player_x = cub->conf.pl_x \
			+ cos(cub->player.rotation_angle) * cub->player.walk_speed;
	else if (cub->player.walk_direction == -1)
		*new_player_x = cub->conf.pl_x \
			- cos(cub->player.rotation_angle) * cub->player.walk_speed;
}

void
	set_new_player_y(t_cub *cub, float *new_player_y)
{
	if (cub->player.side_direction == 1)
		*new_player_y = cub->conf.pl_y \
			+ sin(cub->player.rotation_angle + PI / 2) * cub->player.walk_speed;
	else if (cub->player.side_direction == -1)
		*new_player_y = cub->conf.pl_y \
			- sin(cub->player.rotation_angle + PI / 2) * cub->player.walk_speed;
	else if (cub->player.walk_direction == 1)
		*new_player_y = cub->conf.pl_y \
			+ sin(cub->player.rotation_angle) * cub->player.walk_speed;
	else if (cub->player.walk_direction == -1)
		*new_player_y = cub->conf.pl_y \
			- sin(cub->player.rotation_angle) * cub->player.walk_speed;
}

void
	set_new_rotation_angle(t_cub *cub)
{
	if (cub->player.turn_direction == 1)
		cub->player.rotation_angle += 1 * cub->player.turn_speed;
	else if (cub->player.turn_direction == -1)
		cub->player.rotation_angle -= 1 * cub->player.turn_speed;
}

void
	move(t_cub *cub)
{
	float new_player_x = cub->conf.pl_x;
	float new_player_y = cub->conf.pl_y;

	set_new_player_x(cub, &new_player_x);
	set_new_player_y(cub, &new_player_y);
	set_new_rotation_angle(cub);
	if (!map_has_wall_at(cub, new_player_x, new_player_y))
	{
		cub->conf.pl_x = new_player_x;
		cub->conf.pl_y = new_player_y;
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
	search_sprite_index(int x, int y, t_cub *cub)
{
	int i = 0;
	while (i < cub->sprite_num)
	{
		if (cub->sprite[i].sprite_x == x && cub->sprite[i].sprite_y == y)
			return (i);
		i++;
	}
	return (-1);
}

void
	map_has_sprite_at(float x, float y, t_cub *cub)
{
	float	x_to_check;
	float	y_to_check;
	int		index;

	// TODO: ここでエラー処理必要か確認
	if (x < 0 || x >= cub->conf.map_x * TILE_SIZE \
			|| y < 0 || y > cub->conf.map_y * TILE_SIZE)
		return ;
	x_to_check = floor(x / TILE_SIZE);
	y_to_check = floor(y / TILE_SIZE);
	if (!((int)y_to_check < 0 || (int)x_to_check < 0 \
				|| (int)y_to_check >= cub->conf.map_y \
				|| (int)x_to_check >= cub->conf.map_x))
	{
		if ((cub->conf.map)[(int)y_to_check][(int)x_to_check] == '2')
		{
			index = search_sprite_index((int)x_to_check, (int)y_to_check, cub);
			if (index >= 0)
				cub->sprite[index].visible = 1;
		}
	}
}

void
	set_ray_facing(t_cub *cub, float ray_angle)
{
	cub->cast.is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	cub->cast.is_ray_facing_up = !cub->cast.is_ray_facing_down;
	cub->cast.is_ray_facing_right = \
		ray_angle < PI / 2 || ray_angle > PI * 3 / 2;
	cub->cast.is_ray_facing_left = !cub->cast.is_ray_facing_right;
}

void
	init_horz_wall_hit(t_cub *cub)
{
	cub->cast.found_horz_wall_hit = FALSE;
	cub->cast.horz_wall_hit_x = 0;
	cub->cast.horz_wall_hit_y = 0;
	cub->cast.horz_wall_content = '\0';
}

void
	set_horz_intercept_step(t_cub *cub, float ray_angle)
{
	cub->cast.y_intercept = floor(cub->conf.pl_y / TILE_SIZE) * TILE_SIZE;
	cub->cast.y_intercept += cub->cast.is_ray_facing_down ? TILE_SIZE : 0;
	cub->cast.x_intercept = \
		cub->conf.pl_x + (cub->cast.y_intercept - cub->conf.pl_y) \
		/ tan(ray_angle);
	cub->cast.y_step = TILE_SIZE;
	cub->cast.y_step *= cub->cast.is_ray_facing_up ? -1 : 1;
	cub->cast.x_step = TILE_SIZE / tan(ray_angle);
	cub->cast.x_step *= \
		(cub->cast.is_ray_facing_left && cub->cast.x_step > 0) ? -1 : 1;
	cub->cast.x_step *= \
		(cub->cast.is_ray_facing_right && cub->cast.x_step < 0) ? -1 : 1;
}

void
	set_horz_next_touch(t_cub *cub)
{
	cub->cast.next_horz_touch_x = cub->cast.x_intercept;
	cub->cast.next_horz_touch_y = cub->cast.y_intercept;
}

int
	check_horz_wall_set(t_cub *cub, float x_to_check, float y_to_check)
{
	if (map_has_wall_at(cub, x_to_check, y_to_check))
	{
		cub->cast.horz_wall_hit_x = cub->cast.next_horz_touch_x;
		cub->cast.horz_wall_hit_y = cub->cast.next_horz_touch_y;
		if (!((int)floor(y_to_check / TILE_SIZE) < 0 \
			|| (int)floor(x_to_check / TILE_SIZE) < 0 \
			||(int)floor(y_to_check / TILE_SIZE) >= cub->conf.map_y \
			|| (int)floor(x_to_check / TILE_SIZE) >= cub->conf.map_x))
			cub->cast.horz_wall_content = \
				(cub->conf.map)[(int)floor(y_to_check / TILE_SIZE)]\
				[(int)floor(x_to_check / TILE_SIZE)];
		else
			cub->cast.horz_wall_content = '1';
		cub->cast.found_horz_wall_hit = TRUE;
		return (TRUE);
	}
	else
	{
		cub->cast.next_horz_touch_x += cub->cast.x_step;
		cub->cast.next_horz_touch_y += cub->cast.y_step;
		return (FALSE);
	}
}

void
	set_horz_wall_hit(t_cub *cub)
{
	float x_to_check;
	float y_to_check;

	while (cub->cast.next_horz_touch_x >= 0 \
			&& cub->cast.next_horz_touch_x <= cub->conf.map_x * TILE_SIZE \
			&& cub->cast.next_horz_touch_y >= 0 \
			&& cub->cast.next_horz_touch_y <= cub->conf.map_y * TILE_SIZE)
	{
		x_to_check = cub->cast.next_horz_touch_x;
		y_to_check = cub->cast.next_horz_touch_y + (cub->cast.is_ray_facing_up ? -1 : 0);
		map_has_sprite_at(x_to_check, y_to_check, cub);
		if (check_horz_wall_set(cub, x_to_check, y_to_check) == TRUE)
			break ;
	}
}

void
	init_vert_wall_hit(t_cub *cub)
{
	cub->cast.found_vert_wall_hit = FALSE;
	cub->cast.vert_wall_hit_x = 0;
	cub->cast.vert_wall_hit_y = 0;
	cub->cast.vert_wall_content = '\0';
}

void
	set_vert_intercept_step(t_cub *cub, float ray_angle)
{
	cub->cast.x_intercept = floor(cub->conf.pl_x / TILE_SIZE) * TILE_SIZE;
	cub->cast.x_intercept += cub->cast.is_ray_facing_right ? TILE_SIZE : 0;
	cub->cast.y_intercept = \
		cub->conf.pl_y + (cub->cast.x_intercept - cub->conf.pl_x) \
		* tan(ray_angle);
	cub->cast.x_step = TILE_SIZE;
	cub->cast.x_step *= cub->cast.is_ray_facing_left ? -1 : 1;
	cub->cast.y_step = TILE_SIZE * tan(ray_angle);
	cub->cast.y_step *= \
		(cub->cast.is_ray_facing_up && cub->cast.y_step > 0) ? -1 : 1;
	cub->cast.y_step *= \
		(cub->cast.is_ray_facing_down && cub->cast.y_step < 0) ? -1 : 1;
}

void
	set_vert_next_touch(t_cub *cub)
{
	cub->cast.next_vert_touch_x = cub->cast.x_intercept;
	cub->cast.next_vert_touch_y = cub->cast.y_intercept;
}

int
	check_vert_wall_set(t_cub *cub, float x_to_check, float y_to_check)
{
	if (map_has_wall_at(cub, x_to_check, y_to_check))
	{
		cub->cast.vert_wall_hit_x = cub->cast.next_vert_touch_x;
		cub->cast.vert_wall_hit_y = cub->cast.next_vert_touch_y;
		if (!(\
			(int)floor(y_to_check / TILE_SIZE) < 0 \
			|| (int)floor(x_to_check / TILE_SIZE) < 0 \
			||(int)floor(y_to_check / TILE_SIZE) >= cub->conf.map_y \
			|| (int)floor(x_to_check / TILE_SIZE) >= cub->conf.map_x))
			cub->cast.vert_wall_content = \
				(cub->conf.map)[(int)floor(y_to_check / TILE_SIZE)]\
				[(int)floor(x_to_check / TILE_SIZE)];
		else
			cub->cast.vert_wall_content = '1';
		cub->cast.found_vert_wall_hit = TRUE;
		return (TRUE);
	}
	else
	{
		cub->cast.next_vert_touch_x += cub->cast.x_step;
		cub->cast.next_vert_touch_y += cub->cast.y_step;
		return (FALSE);
	}
}

void
	set_vert_wall_hit(t_cub *cub)
{
	float x_to_check;
	float y_to_check;

	while (cub->cast.next_vert_touch_x >= 0 \
			&& cub->cast.next_vert_touch_x <= cub->conf.map_x * TILE_SIZE \
			&& cub->cast.next_vert_touch_y >= 0 \
			&& cub->cast.next_vert_touch_y <= cub->conf.map_y * TILE_SIZE)
	{
		x_to_check = cub->cast.next_vert_touch_x + (cub->cast.is_ray_facing_left ? -1 : 0);
		y_to_check = cub->cast.next_vert_touch_y;
		map_has_sprite_at(x_to_check, y_to_check, cub);
		if (check_vert_wall_set(cub, x_to_check, y_to_check) == TRUE)
			break ;
	}
}

void
	set_hit_distance(t_cub *cub)
{
	cub->cast.horz_hit_distance = cub->cast.found_horz_wall_hit
		? dist_between_points(cub->conf.pl_x, cub->conf.pl_y\
			, cub->cast.horz_wall_hit_x, cub->cast.horz_wall_hit_y)
		: FLT_MAX;
	cub->cast.vert_hit_distance = cub->cast.found_vert_wall_hit
		? dist_between_points(cub->conf.pl_x, cub->conf.pl_y\
			, cub->cast.vert_wall_hit_x, cub->cast.vert_wall_hit_y)
		: FLT_MAX;
}

void
	set_ray_info(t_cub *cub, int strip_id, float ray_angle)
{
	if (cub->cast.vert_hit_distance < cub->cast.horz_hit_distance)
	{
		cub->rays[strip_id].distance = cub->cast.vert_hit_distance;
		cub->rays[strip_id].wall_hit_x = cub->cast.vert_wall_hit_x;
		cub->rays[strip_id].wall_hit_y = cub->cast.vert_wall_hit_y;
		cub->rays[strip_id].wall_hit_content = cub->cast.vert_wall_content;
		cub->rays[strip_id].was_hit_vertical = TRUE;
	}
	else
	{
		cub->rays[strip_id].distance = cub->cast.horz_hit_distance;
		cub->rays[strip_id].wall_hit_x = cub->cast.horz_wall_hit_x;
		cub->rays[strip_id].wall_hit_y = cub->cast.horz_wall_hit_y;
		cub->rays[strip_id].wall_hit_content = cub->cast.horz_wall_content;
		cub->rays[strip_id].was_hit_vertical = FALSE;
	}
	cub->rays[strip_id].ray_angle = ray_angle;
	cub->rays[strip_id].is_ray_facing_down = cub->cast.is_ray_facing_down;
	cub->rays[strip_id].is_ray_facing_up = cub->cast.is_ray_facing_up;
	cub->rays[strip_id].is_ray_facing_left = cub->cast.is_ray_facing_left;
	cub->rays[strip_id].is_ray_facing_right = cub->cast.is_ray_facing_right;
}

void 
	cast_ray(float ray_angle, int strip_id, t_cub *cub)
{
	ray_angle = normalize_angle(ray_angle);
	set_ray_facing(cub, ray_angle);

	// horizontal ray_grid intersection code
	init_horz_wall_hit(cub);
	set_horz_intercept_step(cub, ray_angle);
	set_horz_next_touch(cub);
	set_horz_wall_hit(cub);
	// vertical ray_grid intersection code
	init_vert_wall_hit(cub);
	set_vert_intercept_step(cub, ray_angle);
	set_vert_next_touch(cub);
	set_vert_wall_hit(cub);
	set_hit_distance(cub);
	set_ray_info(cub, strip_id, ray_angle);
}

void
	cast_all_rays(t_cub *cub)
{
	int		strip_id;
	float	ray_angle;

	strip_id = 0;
	ray_angle = cub->player.rotation_angle - (FOV_ANGLE / 2);
	while (strip_id < cub->conf.win_w)
	{
		cast_ray(ray_angle, strip_id, cub);
		strip_id++;
		ray_angle += FOV_ANGLE / cub->conf.win_w;
	}
}

/*
int
	setting_ray_point(t_cub *cub)
{
	int x = -1;
	int y = -1;
	int i = 0;

	while (i < cub->conf.win_w)
	{
		if (!(cub->rays[i].img_ptr = mlx_new_image(cub->cub_ptr, 20 / MINIMAP_SCALE_FACTOR, 20 / MINIMAP_SCALE_FACTOR)))
		{
			free_cub_map(cub);
			return (error_mes("Error\n false cub_new_image for ray image\n", FALSE));
		}
		cub->rays[i].data = (int *)mlx_get_data_addr(cub->rays[i].img_ptr, &(cub->rays[i].bpp), &(cub->rays[i].size_l), &(cub->rays[i].endian));
		y = -1;
		while (++y < 20 / MINIMAP_SCALE_FACTOR)
		{
			x = -1;
			while (++x < 20 / MINIMAP_SCALE_FACTOR)
			{
				cub->rays[i].data[y * (cub->rays[i].size_l / 4) + x] = 0xff0000;
			}
		}
		i++;
	}
	return (TRUE);
}
*/

/*
void
	put_rays(t_cub *cub)
{
	int i = 0;

	while (i < cub->conf.win_w)
	{
		// all ray put func from here
		r = 0;
		while (r < cub->rays[i].distance / MINIMAP_SCALE_FACTOR)
		{
			mlx_pixel_put(cub->cub_ptr, cub->win, cub->conf.pl_x / MINIMAP_SCALE_FACTOR + (r * cos(cub->rays[i].ray_angle)), cub->conf.pl_y / MINIMAP_SCALE_FACTOR + (r * sin(cub->rays[i].ray_angle)), 0x00FF00);
			r++;
		}
		// till here
		mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->rays[i].img_ptr, (cub->rays[i].wall_hit_x * cub->conf.win_w) / (cub->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR), (cub->rays[i].wall_hit_y * cub->conf.win_h) / (cub->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
		i++;
	}
}
*/

void
	add_some_pi(t_cub *cub, float base, float height, int i)
{
	if (base < 0 && height < 0)
		cub->sprite[i].angle_from_player = \
			PI + cub->sprite[i].angle_from_player;
	else if (base >= 0 && height < 0)
		cub->sprite[i].angle_from_player = \
			2 * PI + cub->sprite[i].angle_from_player;
	else if (base >= 0 && height >= 0)
		cub->sprite[i].angle_from_player = \
			cub->sprite[i].angle_from_player;
	else
		cub->sprite[i].angle_from_player = \
			PI + cub->sprite[i].angle_from_player;
}

void
	get_info_sprite(t_cub *cub)
{
	int i = 0;
	float	base;
	float	height;

	while (i < cub->sprite_num)
	{
		if (cub->sprite[i].visible == 1)
		{
			base = (cub->sprite[i].sprite_x + 0.5) \
					* TILE_SIZE - cub->conf.pl_x;
			height = (cub->sprite[i].sprite_y + 0.5) \
					* TILE_SIZE - cub->conf.pl_y;
			cub->sprite[i].distance = dist_between_points( \
					(cub->sprite[i].sprite_x + 0.5) * TILE_SIZE, \
					(cub->sprite[i].sprite_y + 0.5) * TILE_SIZE, \
					cub->conf.pl_x, \
					cub->conf.pl_y);
			cub->sprite[i].angle_from_player = atanf(height / base);
			add_some_pi(cub, base, height, i);
		}
		i++;
	}
}

void
	copy_sprite_first_half(t_cub *cub, int mid, int i)
{
	while (i <= mid)
	{
		cub->tmp[i] = cub->sprite[i];
		i++;
	}
}

void
	copy_sprite_second_half(t_cub *cub, int right, int i, int j)
{
	while (i <= right)
	{
		cub->tmp[i] = cub->sprite[j];
		i++;
		j--;
	}
}

void
	sort_by_dist(t_cub *cub, int left, int right)
{
	int i;
	int j;
	int k;

	i = left;
	j = right;
	k = left;
	while (k <= right)
	{
		if (cub->tmp[i].distance >= cub->tmp[j].distance)
		{
			cub->sprite[k] = cub->tmp[i];
			i++;
		}
		else
		{
			cub->sprite[k] = cub->tmp[j];
			j--;
		}
		k++;
	}
}

void
	mergesort_sprite_structure(t_cub *cub, int left, int right)
{
	int mid;

	if (left >= right)
		return ;
	mid = (left + right) / 2;
	mergesort_sprite_structure(cub, left, mid);
	mergesort_sprite_structure(cub, mid + 1, right);
	copy_sprite_first_half(cub, mid, left);
	copy_sprite_second_half(cub, right, mid + 1, right);
	sort_by_dist(cub, left, right);
}

void
	sort_sprite_structure(t_cub *cub)
{
	ft_bzero(cub->tmp, sizeof(t_sprites) * (cub->sprite_num + 1));
	mergesort_sprite_structure(cub, 0, cub->sprite_num - 1);
}

void
	set_window_vars(t_cub *cub, int i)
{
	cub->window.perp_distance = cub->rays[i].distance \
				* cos(cub->rays[i].ray_angle - cub->player.rotation_angle);
	cub->window.distance_proj_plane = \
				(cub->conf.win_w / 2) / tan(FOV_ANGLE / 2);
	cub->window.projected_wall_height = (TILE_SIZE \
			/ cub->window.perp_distance) * cub->window.distance_proj_plane;
	cub->window.wall_strip_height = (int)cub->window.projected_wall_height;
	cub->window.wall_top_pixel = (cub->conf.win_h / 2) \
				- (cub->window.wall_strip_height / 2);
	cub->window.wall_top_pixel = cub->window.wall_top_pixel < 0 ? \
				 0 : cub->window.wall_top_pixel;
	cub->window.wall_bottom_pixel = (cub->conf.win_h / 2) \
				+ (cub->window.wall_strip_height / 2);
	cub->window.wall_bottom_pixel = \
			cub->window.wall_bottom_pixel > cub->conf.win_h ? \
					cub->conf.win_h : cub->window.wall_bottom_pixel;
}

void
	set_sprite_var(t_cub *cub, int j)
{
	cub->sprite[j].perp_distance = cub->sprite[j].distance \
		* cos(cub->sprite[j].angle_from_player \
		- cub->player.rotation_angle);
	cub->sprite[j].distance_proj_plane = \
		(cub->conf.win_w / 2) / tan(FOV_ANGLE / 2);
	cub->sprite[j].projected_sprite_height = (TILE_SIZE \
		/ cub->sprite[j].perp_distance) \
		* cub->sprite[j].distance_proj_plane;
	cub->sprite[j].sprite_strip_height = \
		(int)cub->sprite[j].projected_sprite_height;
	cub->sprite[j].sprite_top_pixel = (cub->conf.win_h / 2) \
		- (cub->sprite[j].sprite_strip_height / 2);
	cub->sprite[j].sprite_top_pixel = cub->sprite[j].sprite_top_pixel \
		< 0 ? 0 : cub->sprite[j].sprite_top_pixel;
	cub->sprite[j].sprite_bottom_pixel = (cub->conf.win_h / 2) \
		+ (cub->sprite[j].sprite_strip_height / 2);
	cub->sprite[j].sprite_bottom_pixel = \
		cub->sprite[j].sprite_bottom_pixel > cub->conf.win_h ? \
		cub->conf.win_h : cub->sprite[j].sprite_bottom_pixel;
}

void
	set_sprite_vars(t_cub *cub)
{
	int j;

	j = 0;
	while (j < cub->sprite_num)
	{
		if (cub->sprite[j].visible == 1)
			set_sprite_var(cub, j);
		j++;
	}
}

void
	describe_ceil(t_cub *cub, int x)
{
	int y;

	y = 0;
	while (y < cub->window.wall_top_pixel && y < cub->conf.win_h)
	{
		cub->window.data[((cub->window.size_l / 4) * y) + x] = cub->conf.ceil_c;
		y++;
	}
}

void
	set_tex_offset_x_wall(t_cub *cub, int i)
{
	if (cub->rays[i].was_hit_vertical)
		cub->window.texture_offset_x = \
			(int)cub->rays[i].wall_hit_y % TEXTURE_HEIGHT;
	else
		cub->window.texture_offset_x = \
			(int)cub->rays[i].wall_hit_x % TEXTURE_WIDTH;
}

void
	set_vars_for_wall(t_cub *cub, int i, int *tex_index, int y)
{
	if (cub->rays[i].was_hit_vertical)
		*tex_index = cub->rays[i].is_ray_facing_right ? 2 : 3;
	else
		*tex_index = cub->rays[i].is_ray_facing_up ? 0 : 1;
	cub->window.distance_from_top = \
		y + (cub->window.wall_strip_height / 2) - (cub->conf.win_h / 2);
	cub->window.texture_offset_y = \
		cub->window.distance_from_top \
		* ((float)64 / cub->window.wall_strip_height);
}

void
	describe_wall(t_cub *cub, int i, int x)
{
	int y;
	int tex_index;

	set_tex_offset_x_wall(cub, i);
	y = cub->window.wall_top_pixel;
	while (y < cub->window.wall_bottom_pixel)
	{
		set_vars_for_wall(cub, i, &tex_index, y);
		if (tex_index == 0 || tex_index == 2)
			cub->window.data[((cub->window.size_l / 4) * y) + x] = \
				cub->tex[tex_index].data[((cub->tex[tex_index].size_l / 4) \
				* cub->window.texture_offset_y) + cub->window.texture_offset_x];
		else
		{
			cub->window.texture_offset_x_rev = \
				TEXTURE_WIDTH - cub->window.texture_offset_x - 1;
			cub->window.data[((cub->window.size_l / 4) * y) + x] = \
				cub->tex[tex_index].data[((cub->tex[tex_index].size_l / 4) \
				* cub->window.texture_offset_y) \
				+ cub->window.texture_offset_x_rev];
		}
		y++;
	}
}

void
	describe_floor(t_cub *cub, int x)
{
	int y;

	y = cub->window.wall_bottom_pixel;
	while (y < cub->conf.win_h && y >= 0)
	{
		cub->window.data[((cub->window.size_l / 4) * y) + x] = \
			cub->conf.floor_c;
		y++;
	}
}

int
	check_sprite_visible(t_cub *cub, int i, int j, int x)
{
	if (!(cub->sprite[j].distance < cub->rays[i].distance))
		return (FALSE);
	if (!(cub->sprite[j].visible == 1))
		return (FALSE);
	if (!(x >= ((normalize_angle((cub->sprite[j].angle_from_player \
				- cub->player.rotation_angle) + (FOV_ANGLE / 2)) / FOV_ANGLE) \
				* cub->conf.win_w) \
				- (cub->sprite[j].projected_sprite_height / 2)))
		return (FALSE);
	if (!(x <= ((normalize_angle((cub->sprite[j].angle_from_player \
				- cub->player.rotation_angle) + (FOV_ANGLE / 2)) / FOV_ANGLE) \
				* cub->conf.win_w) \
				+ (cub->sprite[j].projected_sprite_height / 2)))
		return (FALSE);
	return (TRUE);
}

void
	set_tex_offset_x_sprite(t_cub *cub, int j, int x)
{
	cub->sprite[j].texture_offset_x = \
		(int)((x - (((normalize_angle((cub->sprite[j].angle_from_player \
		- cub->player.rotation_angle) + (FOV_ANGLE / 2)) / FOV_ANGLE) \
		* cub->conf.win_w) - (cub->sprite[j].projected_sprite_height / 2))) \
		/ cub->sprite[j].projected_sprite_height * TEXTURE_WIDTH); 
}

void
	set_vars_for_sprite(t_cub *cub, int j, int y)
{
	cub->sprite[j].distance_from_top = \
		y + (cub->sprite[j].sprite_strip_height / 2) - (cub->conf.win_h / 2);
	cub->sprite[j].texture_offset_y = \
		cub->sprite[j].distance_from_top \
		* ((float)64 / cub->sprite[j].sprite_strip_height);
}

void
	set_color_for_sprite(t_cub *cub, int j, int y, int x)
{
	if ((cub->tex[4].data[((cub->tex[4].size_l / 4) \
		* cub->sprite[j].texture_offset_y) \
		+ cub->sprite[j].texture_offset_x] & 0xffffff) != 0 )
	{
		cub->window.data[((cub->window.size_l / 4) * y) + x] = \
			cub->tex[4].data[((cub->tex[4].size_l / 4) \
			* cub->sprite[j].texture_offset_y) \
			+ cub->sprite[j].texture_offset_x];
	}
}

void
	describe_sprite(t_cub *cub, int i, int x)
{
	int y;
	int j;

	j = 0;
	while (j < cub->sprite_num)
	{
		if (check_sprite_visible(cub, i, j, x) == TRUE)
		{
			set_tex_offset_x_sprite(cub, j, x);
			y = cub->sprite[j].sprite_top_pixel;
			while (y < cub->sprite[j].sprite_bottom_pixel)
			{
				set_vars_for_sprite(cub, j, y);
				set_color_for_sprite(cub, j, y, x);
				y++;
			}
		}
		j++;
	}
}

void
	generate_3d_projection(t_cub *cub)
{
	int x;
	int i;

	x = 0;
	while (x < cub->conf.win_w)
	{
		i = x / ceil((double)cub->conf.win_w / (double)cub->conf.win_w);
		set_window_vars(cub, i);
		set_sprite_vars(cub);
		describe_ceil(cub, x);
		describe_wall(cub, i, x);
		describe_floor(cub, x);
		describe_sprite(cub, i, x);
		x++;
	}
}

int
	setting_window(t_cub *cub)
{
	int x = -1;
	int y = -1;

	if (!(cub->window.img_ptr = mlx_new_image(cub->cub_ptr, cub->conf.win_w \
					, cub->conf.win_h)))
	{
		free_cub_map(cub);
		return (FALSE);
	}
	cub->window.data = (int *)mlx_get_data_addr(cub->window.img_ptr \
			, &(cub->window.bpp), &(cub->window.size_l), &(cub->window.endian));
	while (++y < cub->conf.win_h)
	{
		x = -1;
		while (++x < cub->conf.win_w)
		{
			cub->window.data[y * (cub->window.size_l / 4) + x] = 0x000000;
		}
	}
	return (TRUE);
}

void
	reset_sprite_info(t_cub *cub)
{
	int i = 0;
	while (i < cub->sprite_num)
	{
		cub->sprite[i].visible = 0;
		cub->sprite[i].distance = 0;
		i++;
	}
}

int
	rendering_loop(t_cub *cub)
{
	move(cub);
	cast_all_rays(cub);
	get_info_sprite(cub);
	sort_sprite_structure(cub);
	generate_3d_projection(cub);
	mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->window.img_ptr, 0, 0);
//	mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->map.img_ptr, 0, 0);
//	mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->player.img_ptr, (cub->conf.pl_x * cub->conf.win_w) / (cub->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR), (cub->conf.pl_y * cub->conf.win_h) / (cub->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
//	put_line(cub);
//	put_rays(cub);
	reset_sprite_info(cub);
	return (TRUE);
}

int
	rendering_for_bmp(t_cub *cub)
{
	move(cub);
	cast_all_rays(cub);
	get_info_sprite(cub);
	sort_sprite_structure(cub);
	generate_3d_projection(cub);
	mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->window.img_ptr, 0, 0);
//	mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->map.img_ptr, 0, 0);
//	mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->player.img_ptr, (cub->conf.pl_x * cub->conf.win_w) / (cub->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR), (cub->conf.pl_y * cub->conf.win_h) / (cub->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
//	put_line(cub);
//	put_rays(cub);
//	reset_sprite_info(cub);
	return (TRUE);
}

/*
int
	setting_map(t_cub *cub)
{
	int x = -1;
	int y = -1;

	//TODO: leak check again
	if(!(cub->map.img_ptr = mlx_new_image(cub->cub_ptr, cub->conf.win_w / MINIMAP_SCALE_FACTOR, cub->conf.win_h / MINIMAP_SCALE_FACTOR)))
	{
		free_cub_map(cub);
		return (error_mes("Error\n false cub_new_image for map image\n", FALSE));
	}
	cub->map.data = (int *)mlx_get_data_addr(cub->map.img_ptr, &(cub->map.bpp), &(cub->map.size_l), &(cub->map.endian));
	while (++y < cub->conf.win_h / MINIMAP_SCALE_FACTOR)
	{
		x = -1;
		while (++x < cub->conf.win_w / MINIMAP_SCALE_FACTOR)
		{
			cub->map.tile_x = (x * cub->conf.map_x) / (cub->conf.win_w / MINIMAP_SCALE_FACTOR);
			cub->map.tile_y = (y * cub->conf.map_y) / (cub->conf.win_h / MINIMAP_SCALE_FACTOR);
			if ((cub->conf.map)[cub->map.tile_y][cub->map.tile_x] == '0')
				cub->map.data[y * (cub->map.size_l / 4) + x] = 0x020202;
			else if ((cub->conf.map)[cub->map.tile_y][cub->map.tile_x] == '1')
				cub->map.data[y * (cub->map.size_l / 4) + x] = 0xffffff;
		}
	}
	return (TRUE);
}
*/
/*
int
	setting_player(t_cub *cub)
{
	int x = -1;
	int y = -1;

	//TODO: leak check again
	if (!(cub->player.img_ptr = mlx_new_image(cub->cub_ptr, cub->player.width, cub->player.height)))
	{
		free_cub_map(cub);
		return (error_mes("Error\n false cub_new_image for player image\n", FALSE));
	}
	cub->player.data = (int *)mlx_get_data_addr(cub->player.img_ptr, &(cub->player.bpp), &(cub->player.size_l), &(cub->player.endian));
	while (++y < cub->player.height)
	{
		x = -1;
		while (++x < cub->player.width)
		{
			cub->player.data[y * (cub->player.size_l / 4) + x] = 0xFFFF00;
		}
	}
	return (TRUE);
}
*/

int
	check_path_available(t_cub *cub)
{
	int fd[5];
	int i;

	fd[0] = open(cub->conf.path_no, O_RDONLY);
	close(fd[0]);
	fd[1] = open(cub->conf.path_so, O_RDONLY);
	close(fd[1]);
	fd[2] = open(cub->conf.path_ea, O_RDONLY);
	close(fd[2]);
	fd[3] = open(cub->conf.path_we, O_RDONLY);
	close(fd[3]);
	fd[4] = open(cub->conf.path_sp, O_RDONLY);
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
	free_map_ret_error(t_cub *cub, char *str, int ret)
{
	free_cub_map(cub);
	error_mes(str, ret);
	return (ret);
}

int
	get_wall_img_ptr(t_cub *cub)
{
	int width = TEXTURE_WIDTH;
	int height = TEXTURE_HEIGHT;

	width = TEXTURE_WIDTH;
	height = TEXTURE_HEIGHT;
	if (!(cub->tex[0].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr \
					, cub->conf.path_no, &width, &height)))
		return (free_map_ret_error(cub,"Error\n invalid texture file\n" \
					, FALSE));
	if (!(cub->tex[1].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr \
					, cub->conf.path_so, &width, &height)))
		return (free_map_ret_error(cub,"Error\n invalid texture file\n" \
					, FALSE));
	if (!(cub->tex[2].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr \
					, cub->conf.path_ea, &width, &height)))
		return (free_map_ret_error(cub,"Error\n invalid texture file\n" \
					, FALSE));
	if (!(cub->tex[3].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr \
					, cub->conf.path_we, &width, &height)))
		return (free_map_ret_error(cub,"Error\n invalid texture file\n" \
					, FALSE));
	return (TRUE);
}

int
	get_sprite_img_ptr(t_cub *cub)
{
	int width;
	int height;

	width = TEXTURE_WIDTH;
	height = TEXTURE_HEIGHT;
	if (!(cub->tex[4].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr \
					, cub->conf.path_sp, &width, &height)))
		return (free_map_ret_error(cub,"Error\n invalid texture file\n" \
					, FALSE));
	return (TRUE);
}

int
	setting_img(t_cub *cub)
{
	if (!check_path_available(cub))
		return (free_map_ret_error(cub, "Error\n invalid path of texture\n" \
			, FALSE));
	if (get_wall_img_ptr(cub) == FALSE)
		return (FALSE);
	if (get_sprite_img_ptr(cub) == FALSE)
		return (FALSE);
	cub->tex[0].data = (int *)mlx_get_data_addr(cub->tex[0].img_ptr \
			, &(cub->tex[0].bpp), &(cub->tex[0].size_l), &(cub->tex[0].endian));
	cub->tex[1].data = (int *)mlx_get_data_addr(cub->tex[1].img_ptr \
			, &(cub->tex[1].bpp), &(cub->tex[1].size_l), &(cub->tex[1].endian));
	cub->tex[2].data = (int *)mlx_get_data_addr(cub->tex[2].img_ptr \
			, &(cub->tex[2].bpp), &(cub->tex[2].size_l), &(cub->tex[2].endian));
	cub->tex[3].data = (int *)mlx_get_data_addr(cub->tex[3].img_ptr \
			, &(cub->tex[3].bpp), &(cub->tex[3].size_l), &(cub->tex[3].endian));
	cub->tex[4].data = (int *)mlx_get_data_addr(cub->tex[4].img_ptr \
			, &(cub->tex[4].bpp), &(cub->tex[4].size_l), &(cub->tex[4].endian));
	return (TRUE);
}

void
	set_last_sprite(t_cub *cub, int k)
{
	cub->sprite[k].sprite_x =  -1;
	cub->sprite[k].sprite_y = -1;
	cub->sprite[k].visible = -1;
}

void
	count_sprite_num(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	cub->sprite_num = 0;
	while (i < cub->conf.map_y)
	{
		j = 0;
		while (j < cub->conf.map_x)
		{
			if ((cub->conf.map)[i][j] == '2')
				cub->sprite_num++;
			j++;
		}
		i++;
	}
}

int
	set_sprites(t_cub *cub)
{
	int i;
	int j;
	int num;

	i = 0;
	num = 0;
	while (i < cub->conf.map_y)
	{
		j = 0;
		while (j < cub->conf.map_x && num < cub->sprite_num)
		{
			if ((cub->conf.map)[i][j] == '2')
			{
				cub->sprite[num].sprite_y = i;
				cub->sprite[num].sprite_x = j;
				cub->sprite[num].visible = 0;
				num++;
			}
			j++;
		}
		i++;
	}
	return (num);
}

int
	check_sprite_info(t_cub *cub)
{
	int num;

	count_sprite_num(cub);
	if (!(cub->sprite = malloc(sizeof(t_sprites) * (cub->sprite_num + 1))))
		return (FALSE);
	ft_bzero(cub->sprite, sizeof(t_sprites) * (cub->sprite_num + 1));
	if (!(cub->tmp = malloc(sizeof(t_sprites) * (cub->sprite_num + 1))))
	{
		free(cub->sprite);
		cub->sprite = NULL;
		return (FALSE);
	}
	num = set_sprites(cub);
	set_last_sprite(cub, num);
	return (TRUE);
}

int
	initialize_window(t_cub *cub)
{
	if (!(cub->cub_ptr = mlx_init()))
		return (FALSE);
	if (!(cub->win = mlx_new_window(cub->cub_ptr, cub->conf.win_w \
								, cub->conf.win_h, "cub3d_window")))
		return (FALSE);
	return (TRUE);
}

int
	key_release(int key, t_cub *cub)
{
	if (key == KEY_W)
		cub->player.walk_direction = 0;
	if (key == KEY_S)
		cub->player.walk_direction = 0;
	if (key == KEY_D)
		cub->player.side_direction = 0;
	if (key == KEY_A)
		cub->player.side_direction = 0;
	if (key == KEY_RIGHT)
		cub->player.turn_direction = 0;
	if (key == KEY_LEFT)
		cub->player.turn_direction = 0;
	return (TRUE);
}

int
	get_ray_size(t_cub *cub)
{
	if (!(cub->rays = malloc(sizeof(t_rays) * (cub->conf.win_w + 1))))
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
	pack_win_size(t_cub *cub, char *line)
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
	cub->conf.win_w = ft_atoi(strs[1]);
	cub->conf.win_h = ft_atoi(strs[2]);
	if (cub->conf.win_w <= 0 || cub->conf.win_h <= 0)
		return (free_strs(strs, num, FALSE));
	cub->conf.win_w = cub->conf.win_w > cub->conf.win_max_w ? \
								cub->conf.win_max_w : cub->conf.win_w;
	cub->conf.win_h = cub->conf.win_h > cub->conf.win_max_h ? \
								cub->conf.win_max_h : cub->conf.win_h;
	if (get_ray_size(cub) == FALSE)
		return (free_strs(strs, num, FALSE));
	free_str_safe(line);
	return (free_strs(strs, num, TRUE));
}

int
	count_strs(char **strs, int i)
{
	int counter;

	counter = i;
	if (!strs || !strs[counter])
		return (counter);
	while (strs[counter])
		counter++;
	return (counter);
}

int
	pack_path(t_cub *cub, char *line)
{
	char	**strs;
	int		len;

	strs = ft_split(line, ' ');
	if (count_strs(strs, 0) != 2)
		return (free_strs(strs, count_strs(strs, 0), FALSE));
	if (ft_strlen(strs[0]) != 2 \
			&& (ft_strlen(strs[0]) != 1 && ft_strncmp(strs[0], "S", 1)))
		return (free_strs(strs, 2, FALSE));
	len = ft_strlen(strs[1]);
	if (strs[1])
	{
		if (ft_strnstr(strs[0], "NO", 2))
			cub->conf.path_no = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "SO", 2))
			cub->conf.path_so = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "EA", 2))
			cub->conf.path_ea = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "WE", 2))
			cub->conf.path_we = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "S", 1))
			cub->conf.path_sp = ft_substr(strs[1], 0, len);
	}
	free_str_safe(line);
	return (free_strs(strs, 2, TRUE));
}

int
	check_rgb_available(char **strs, t_cub *cub)
{
	int i;
	int j;

	i = 0;
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
		if (cub->conf.floor_colors[i] < 0 || cub->conf.floor_colors[i] > 255 \
			|| cub->conf.ceil_colors[i] < 0 || cub->conf.ceil_colors[i] > 255)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void
	add_color(t_cub *cub)
{
	cub->conf.floor_c = cub->conf.floor_colors[0];
	cub->conf.floor_c = cub->conf.floor_c << 8;
	cub->conf.floor_c = cub->conf.floor_c | cub->conf.floor_colors[1];
	cub->conf.floor_c = cub->conf.floor_c << 8;
	cub->conf.floor_c = cub->conf.floor_c | cub->conf.floor_colors[2];
	cub->conf.ceil_c = cub->conf.ceil_colors[0];
	cub->conf.ceil_c = cub->conf.ceil_c << 8;
	cub->conf.ceil_c = cub->conf.ceil_c | cub->conf.ceil_colors[1];
	cub->conf.ceil_c = cub->conf.ceil_c << 8;
	cub->conf.ceil_c = cub->conf.ceil_c | cub->conf.ceil_colors[2];
}

int
	free_for_pack_rgb(char **sub_strs, char **strs, int len, int ret)
{
	free_strs(sub_strs, 2, 0);
	return (free_strs(strs, len, ret));
}

void
	pack_rgb_atoi(char c, t_cub *cub, char **strs)
{
	if (c == 'F')
	{
		cub->conf.floor_colors[0] = ft_atoi(strs[0]);
		cub->conf.floor_colors[1] = ft_atoi(strs[1]);
		cub->conf.floor_colors[2] = ft_atoi(strs[2]);
	}
	if (c == 'C')
	{
		cub->conf.ceil_colors[0] = ft_atoi(strs[0]);
		cub->conf.ceil_colors[1] = ft_atoi(strs[1]);
		cub->conf.ceil_colors[2] = ft_atoi(strs[2]);
	}
}

int
	pack_rgb(t_cub *cub, char *line)
{
	char	**sub_strs;
	char	**strs;

	sub_strs = ft_split(line, ' ');
	if (count_strs(sub_strs, 0) != 2)
		return (free_strs(sub_strs, count_strs(sub_strs, 0), FALSE));
	strs = ft_split(sub_strs[1], ',');
	if (count_strs(strs, 0) != 3)
		return (free_for_pack_rgb(sub_strs, strs, count_strs(strs, 0), FALSE));
	if (ft_strnstr(sub_strs[0], "F", 1) && ft_strlen(sub_strs[0]) == 1)
		pack_rgb_atoi('F', cub, strs);
	else if (ft_strnstr(sub_strs[0], "C", 1) && ft_strlen(sub_strs[0]) == 1)
		pack_rgb_atoi('C', cub, strs);
	else
		return (free_for_pack_rgb(sub_strs, strs, 3, FALSE));
	if ((cub->conf.cub_flag[6] || cub->conf.cub_flag[7]) \
			&& !check_rgb_available(strs, cub))
		return (free_for_pack_rgb(sub_strs, strs, 3, FALSE));
	add_color(cub);
	free_str_safe(line);
	return (free_for_pack_rgb(sub_strs, strs, 3, TRUE));
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
	pack_map_str(t_cub *cub, char *line)
{
	char *tmp;
	int len;

	if (cub->conf.cub_flag[8] == 1)
	{
		if (!(cub->conf.map_str = malloc(sizeof(char))))
			return (error_mes("Error\n could not malloc for map_str\n"\
			, FALSE));
		*(cub->conf.map_str) = '\0';
	}
	cub->conf.cub_flag[8]++;
	len = ft_strlen(line);
	cub->conf.map_x = max_len(cub->conf.map_x, len);
	tmp = cub->conf.map_str;
	cub->conf.map_str = ft_strjoin(cub->conf.map_str, line);
	free_str_safe(tmp);
	tmp = cub->conf.map_str;
	cub->conf.map_str = ft_strjoin(cub->conf.map_str, "\n");
	cub->conf.map_y++;
	free_str_safe(tmp);
	return (TRUE);
}

int
	conf_fill_checker(t_cub *cub)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (cub->conf.cub_flag[i++] == 0)
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

void
	fill_map_space(t_cub *cub)
{
	int index;
	char *tmp;

	index = 0;
	while (index < cub->conf.map_y)
	{
		while ((int)ft_strlen((cub->conf.map)[index]) < cub->conf.map_x)
		{
			tmp = cub->conf.map[index];
			(cub->conf.map)[index] = ft_strjoin((cub->conf.map)[index], " ");
			free_str_safe(tmp);
		}
		index++;
	}
}

int
	free_line_ret_mes(char *line)
{
	free_str_safe(line);
	return (error_mes("Error\n invalid configure\n", FALSE));
}

int
	check_pack_map_str(t_cub *cub, int *flag, char *line)
{
	if ((cub->conf.cub_flag[8] == 0 \
				&& conf_fill_checker(cub) == FALSE) || *flag == 10)
		return (free_line_ret_mes(line));
	if (check_is_map(line) == FALSE)
	{
		free_str_safe(line);
		return (error_mes("Error\n map is not made by map element\n", FALSE));
	}
	*flag = 9;
	cub->conf.cub_flag[8]++;
	if (pack_map_str(cub, line) == FALSE)
	{
		free_str_safe(line);
		return (FALSE);
	}
	free_str_safe(line);
	return (TRUE);
}

int
	pack_path_update_flag(t_cub *cub, char *line, int *flag, int index)
{
	if (pack_path(cub, line) == FALSE)
		return (free_line_ret_mes(line));
	(*flag)++;
	cub->conf.cub_flag[index] = 1;
	return (TRUE);
}

int
	pack_rgb_update_flag(t_cub *cub, char *line, int *flag, int index)
{
	if (pack_rgb(cub, line) == FALSE)
		return (free_line_ret_mes(line));
	(*flag)++;
	cub->conf.cub_flag[index] = 1;
	return (TRUE);
}

int
	check_texture_line(char *line)
{
	if (ft_strnstr(line, "NO", 2))
		return (1);
	else if (ft_strnstr(line, "SO", 2))
		return (2);
	else if (ft_strnstr(line, "EA", 2))
		return (3);
	else if (ft_strnstr(line, "WE", 2))
		return (4);
	else if (ft_strnstr(line, "S", 1))
		return (5);
	return (FALSE);
}

int
	check_rgb_line(char *line)
{
	if (ft_strnstr(line, "F", 1))
		return (6);
	else if (ft_strnstr(line, "C", 1))
		return (7);
	return (FALSE);
}

void
	pass_empty_line(char *line, int *flag)
{
	free_str_safe(line);
	if (*flag == 9)
		*flag = 10;
}

int
	pack_wsize_update_flag(t_cub *cub, char *line, int *flag)
{
		if (pack_win_size(cub, line) == FALSE)
			return (free_line_ret_mes(line));
		(*flag)++;
		cub->conf.cub_flag[0] = 1;
		return (TRUE);
}

int
	pack_line_each_info(t_cub *cub, int *flag, char *line, int *index)
{
	if (!*line)
		pass_empty_line(line, flag);
	else if (*flag >= 8)
	{
		if (check_pack_map_str(cub, flag, line) == FALSE)
			return (FALSE);
	}
	else if (ft_strnstr(line, "R", 1))
	{
		if (pack_wsize_update_flag(cub, line, flag) == FALSE)
			return (FALSE);
	}
	else if ((*index = check_texture_line(line)) != FALSE )
	{
		if (pack_path_update_flag(cub, line, flag, *index) == FALSE)
			return (FALSE);
	}
	else if ((*index = check_rgb_line(line)) != FALSE )
	{
		if (pack_rgb_update_flag(cub, line, flag, *index) == FALSE)
			return (FALSE);
	}
	else
		return (free_line_ret_mes(line));
	return (TRUE);
}

int
	get_conf(t_cub *cub, char *file_name)
{
	int fd;
	int res;
	int flag;
	int index;
	char *line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (error_mes("Error\n invalid fd\n", FALSE));
	flag = 0;
	while ((res = get_next_line(fd, &line)))
	{
		if (res == -1)
			return (error_mes("Error\n some error while gnl working\n", FALSE));
		if (pack_line_each_info(cub, &flag, line, &index) == FALSE)
			return (FALSE);
	}
	cub->conf.map = ft_split(cub->conf.map_str, '\n');
	fill_map_space(cub);
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
	check_fill(char *map_p, int p_y, int p_x, t_cub *cub)
{
	if (map_p[p_y * (cub->conf.map_x + 2) + p_x] == 'p' \
			|| map_p[p_y * (cub->conf.map_x + 2) + p_x] == '1' \
			|| map_p[p_y * (cub->conf.map_x + 2) + p_x] == '3' \
			|| cub->conf.map_check_flag == 1)
		return ;
	if (map_p[p_y * (cub->conf.map_x + 2) + p_x] == 'X')
	{
		cub->conf.map_check_flag = 1;
		return ;
	}
	if (map_p[p_y * (cub->conf.map_x + 2) + p_x] == '0' \
			|| map_p[p_y * (cub->conf.map_x + 2) + p_x] == 's')
		map_p[p_y * (cub->conf.map_x + 2) + p_x] = 'p';
	if (map_p[p_y * (cub->conf.map_x + 2) + p_x] == '2')
		map_p[p_y * (cub->conf.map_x + 2) + p_x] = '3';
	check_fill(map_p, p_y - 1, p_x, cub);
	check_fill(map_p, p_y, p_x + 1, cub);
	check_fill(map_p, p_y + 1, p_x, cub);
	check_fill(map_p, p_y, p_x - 1, cub);
}

void
	put_grid_to_container(t_cub *cub, char *cont_p)
{
	int i;
	int j;

	i = 0;
	while (i < cub->conf.map_y + 2)
	{
		j = 0;
		while (j < cub->conf.map_x + 2)
		{
			if (i == 0 || i == cub->conf.map_y + 1 || j == 0 \
					|| j == cub->conf.map_x + 1)
				cont_p[i * (cub->conf.map_x + 2) + j] = 'X';
			else if (i > cub->conf.map_y || j > cub->conf.map_x \
					|| (cub->conf.map)[i - 1][j - 1] == ' ')
				cont_p[i * (cub->conf.map_x + 2) + j] = 's';
			else
				cont_p[i * (cub->conf.map_x + 2) + j] \
					= (cub->conf.map)[i - 1][j - 1];
			j++;
		}
		i++;
	}
}

int
	check_player_exist(char spot, t_cub *cub)
{
	if (spot == 'N' || spot == 'S' || spot == 'E' || spot == 'W')
	{
		if (spot == 'N')
			cub->player.rotation_angle = 270 * (PI / 180);
		else if (spot == 'S')
			cub->player.rotation_angle = 90 * (PI / 180);
		else if (spot == 'E')
			cub->player.rotation_angle = 0 * (PI / 180);
		else if (spot == 'W')
			cub->player.rotation_angle = 180 * (PI / 180);
		cub->conf.pl_counter++;
		return (TRUE);
	}
	return (FALSE);
}

int
	pick_player_pl(char *cont_p, int *player_y, int *player_x, t_cub *cub)
{
	int i;
	int j;
	int x;

	x = cub->conf.map_x + 2;
	i = 0;
	while (i < cub->conf.map_y + 2)
	{
		j = 0;
		while (j < x)
		{
			if (check_player_exist(cont_p[i * x + j], cub) == TRUE)
			{
				*player_y = i;
				*player_x = j;
			}
			j++;
		}
		i++;
	}
	if (cub->conf.pl_counter == 1)
		return (TRUE);
	free_str_safe(cont_p);
	return (FALSE);
}

int
	check_map(t_cub *cub)
{
	int player_x;
	int player_y;
	char *cont_p;

	cont_p = malloc(sizeof(char) \
		* (cub->conf.map_y + 2) * (cub->conf.map_x + 2));
	put_grid_to_container(cub, cont_p);
	if (!pick_player_pl(cont_p, &player_y, &player_x, cub))
	{
		free_cub_map(cub);
		return (error_mes("Error\n No player or more than 2 players\n" \
			, FALSE));
	}
	check_fill(cont_p, player_y, player_x, cub);
	if (cub->conf.map_check_flag == 1)
	{
		free_cub_map(cub);
		free_str_safe(cont_p);
		return (error_mes("Error\n Map is not sorrounded by wall.\n", FALSE));
	}
	cub->conf.pl_y = player_y - 1;
	cub->conf.pl_x = player_x - 1;
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
	init_vars(t_cub *cub)
{
	int i;

	ft_bzero(cub, sizeof(t_cub));
	i = 0;
	while (i < 9)
		ft_bzero(&(cub->conf.cub_flag[i++]), sizeof(int));
}

void
	make_img(t_cub *cub, int fd)
{
	int	x;
	int	y;
	int	color;

	y = cub->conf.win_h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < cub->conf.win_w)
		{
			color = cub->window.data[((cub->window.size_l / 4) * y) + x];
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

void
	make_header(t_cub *cub, int fd, unsigned int header_size \
			, unsigned int img_size)
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
	write(fd, &(cub->conf.win_w), 4);
	write(fd, &(cub->conf.win_h), 4);
	plane = 1;
	write(fd, &plane, 2);
	write(fd, &(cub->window.bpp), 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &img_size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

int
	create_bmp(t_cub *cub)
{
	int	fd;
	unsigned int	img_size;
	unsigned int	header_size;

	rendering_for_bmp(cub);
	if ((fd = open("image.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
	{
		close(fd);
		free_cub_map(cub);
		return (FALSE);
	}
	img_size = (unsigned int)(cub->conf.win_w * cub->conf.win_h) \
		* (cub->window.bpp / 8);
	header_size = 54;
	make_header(cub, fd, header_size, img_size);
	make_img(cub, fd);
	free_cub_map(cub);
	free_cub(cub, TRUE);
	exit (0);
}

int
	main(int ac, char **av)
{
	t_cub	cub;

	if (ac <= 1 || ac > 3)
		return (error_mes("Error\n few args or too many args\n", ERROR));
	if ((ac == 3 && !save_checker(av[2])) || (ac == 3 && !save_checker(av[2])))
		return (error_mes("Error\n invalid args\n", ERROR));
	init_vars(&cub);
	mlx_get_screen_size(cub.cub_ptr \
		, &(cub.conf.win_max_w), &(cub.conf.win_max_h));
	if (get_conf(&cub, av[1]) == FALSE || check_map(&cub) == FALSE)
		return (free_cub(&cub, ERROR));
	cub_conf(&cub);
	if (!(initialize_window(&cub)) || setting_img(&cub) == FALSE \
		|| setting_window(&cub) == FALSE)
		return (free_cub(&cub, ERROR));
/*
//	if (setting_map(&cub) == FALSE)
//		return (free_cub(&cub, ERROR));
//	if (setting_player(&cub) == FALSE)
//		return (free_cub(&cub, ERROR));
//	if (setting_ray_point(&cub) == FALSE)
//		return (free_cub(&cub, ERROR));
*/
	if (check_sprite_info(&cub) == FALSE \
			|| (ac == 3 && create_bmp(&cub) == FALSE))
		return (free_cub(&cub, ERROR));
	mlx_hook(cub.win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &cub);
	mlx_hook(cub.win, 17, 1 << 17, &close_button_press, &cub);
	mlx_hook(cub.win, X_EVENT_KEY_RELEASE, 1L<<1, &key_release, &cub);
	mlx_loop_hook(cub.cub_ptr, &rendering_loop, &cub);
	mlx_loop(cub.cub_ptr);
	return (TRUE);
}
