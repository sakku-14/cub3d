/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:32:38 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 14:48:03 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include "../minilibx_mms_20200219/mlx.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

# define FALSE					0
# define TRUE					1
# define ERROR					-1
# define STDERR					2
# define PI						3.1415926535
# define TILE_SIZE				64
# define MINIMAP_SCALE_FACTOR	4
# define MAP_NUM_ROWS			13
# define MAP_NUM_COLS			20
# define TEXTURE_WIDTH			64
# define TEXTURE_HEIGHT			64
# define FOV_ANGLE				1.04719755117
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# define X_EVENT_BTN_PRESS		4
# define KEY_ESC				53
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_UP					126
# define KEY_DOWN				125
# define KEY_A					0
# define KEY_D					2
# define KEY_W					13
# define KEY_S					1

typedef struct	s_player
{
	float		rotation_angle;
	int			turn_direction;
	int			walk_direction;
	int			side_direction;
	float		walk_speed;
	float		turn_speed;
}				t_player;

typedef struct	s_window
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	float		perp_distance;
	float		distance_proj_plane;
	float		projected_wall_height;
	int			wall_strip_height;
	int			wall_top_pixel;
	int			wall_bottom_pixel;
	int			distance_from_top;
	int			texture_offset_x;
	int			texture_offset_x_rev;
	int			texture_offset_y;
}				t_window;

typedef struct	s_rays
{
	float		ray_angle;
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	int			was_hit_vertical;
	int			is_ray_facing_up;
	int			is_ray_facing_down;
	int			is_ray_facing_right;
	int			is_ray_facing_left;
	int			wall_hit_content;
}				t_rays;

typedef struct	s_tex
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_tex;

typedef	struct	s_sprites
{
	float		sprite_x;
	float		sprite_y;
	int			visible;
	float		distance;
	float		angle_from_player;
	float		perp_distance;
	float		distance_proj_plane;
	float		projected_sprite_height;
	int			sprite_strip_height;
	int			sprite_top_pixel;
	int			sprite_bottom_pixel;
	int			distance_from_top;
	int			texture_offset_x;
	int			texture_offset_y;
}				t_sprites;

typedef struct	s_conf
{
	int			win_w;
	int			win_h;
	int			win_max_w;
	int			win_max_h;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	char		*path_sp;
	int			floor_colors[3];
	int			floor_c;
	int			ceil_colors[3];
	int			ceil_c;
	int			cub_flag[9];
	char		*map_str;
	char		**map;
	char		*cont_p;
	int			map_y;
	int			map_x;
	int			map_check_flag;
	float		pl_y;
	float		pl_x;
	int			pl_counter;
	int			rays_free_flag;
}				t_conf;

typedef	struct	s_castinfo
{
	int			is_ray_facing_down;
	int			is_ray_facing_up;
	int			is_ray_facing_right;
	int			is_ray_facing_left;
	float		x_intercept;
	float		y_intercept;
	float		x_step;
	float		y_step;
	int			found_horz_wall_hit;
	float		horz_wall_hit_x;
	float		horz_wall_hit_y;
	char		horz_wall_content;
	float		next_horz_touch_x;
	float		next_horz_touch_y;
	float		x_to_check;
	float		y_to_check;
	int			found_vert_wall_hit;
	float		vert_wall_hit_x;
	float		vert_wall_hit_y;
	char		vert_wall_content;
	float		next_vert_touch_x;
	float		next_vert_touch_y;
	float		horz_hit_distance;
	float		vert_hit_distance;
}				t_castinfo;

typedef struct	s_cub
{
	void		*cub_ptr;
	void		*win;
	t_player	player;
	t_window	window;
	t_rays		*rays;
	t_castinfo	cast;
	t_sprites	*sprite;
	t_sprites	*tmp;
	t_conf		conf;
	int			sprite_num;
	t_tex		tex[5];
}				t_cub;

void			make_img(t_cub *cub, int fd);
void			make_header(t_cub *cub, int fd, unsigned int header_size,
					unsigned int img_size);
int				rendering_for_bmp(t_cub *cub);
int				create_bmp(t_cub *cub);
float			normalize_angle(float angle);
void			set_ray_facing(t_cub *cub, float ray_angle);
void			init_horz_wall_hit(t_cub *cub);
void			set_horz_intercept_step(t_cub *cub, float ray_angle);
void			set_horz_next_touch(t_cub *cub);
int				check_horz_wall_set(t_cub *cub, float x_to_check,
					float y_to_check);
int				search_sprite_index(int x, int y, t_cub *cub);
void			map_has_sprite_at(float x, float y, t_cub *cub);
void			set_horz_wall_hit(t_cub *cub);
void			init_vert_wall_hit(t_cub *cub);
void			set_vert_intercept_step(t_cub *cub, float ray_angle);
void			set_vert_next_touch(t_cub *cub);
int				check_vert_wall_set(t_cub *cub, float x_to_check,
					float y_to_check);
void			set_vert_wall_hit(t_cub *cub);
void			set_hit_distance(t_cub *cub);
void			set_ray_info(t_cub *cub, int strip_id, float ray_angle);
void			cast_ray(float ray_angle, int strip_id, t_cub *cub);
void			cast_all_rays(t_cub *cub);
void			check_fill(char *map_p, int p_y, int p_x, t_cub *cub);
int				check_player_exist(char spot, t_cub *cub);
int				pick_player_pl(char *cont_p, int *player_y, int *player_x,
					t_cub *cub);
void			put_grid_to_container(t_cub *cub, char *cont_p);
int				check_map(t_cub *cub);
int				check_path_available(t_cub *cub);
float			dist_between_points(float x1, float y1, float x2, float y2);
void			cub_conf(t_cub *cub);
int				error_mes(char *str, int ret);
void			free_str_safe(char *str);
int				free_strs(char **strs, int num, int ret);
void			free_cub_map(t_cub *cub);
void			free_rays(t_cub *cub);
int				free_cub(t_cub *cub, int ret);
void			set_window_vars(t_cub *cub, int i);
void			set_sprite_var(t_cub *cub, int j);
void			set_sprite_vars(t_cub *cub);
void			describe_ceil(t_cub *cub, int x);
void			set_tex_offset_x_wall(t_cub *cub, int i);
void			set_vars_for_wall(t_cub *cub, int i, int *tex_index, int y);
void			describe_wall(t_cub *cub, int i, int x);
void			describe_floor(t_cub *cub, int x);
int				check_sprite_visible(t_cub *cub, int i, int j, int x);
void			set_tex_offset_x_sprite(t_cub *cub, int j, int x);
void			set_vars_for_sprite(t_cub *cub, int j, int y);
void			set_color_for_sprite(t_cub *cub, int j, int y, int x);
void			describe_sprite(t_cub *cub, int i, int x);
void			generate_3d_projection(t_cub *cub);
void			pass_empty_line(char *line, int *flag);
int				conf_fill_checker(t_cub *cub);
int				check_c_in_str(char c, char *str);
int				check_is_map(char *line);
int				max_len(int x, int y);
int				pack_map_str(t_cub *cub, char *line);
int				check_pack_map_str(t_cub *cub, int *flag, char *line);
int				get_ray_size(t_cub *cub);
int				is_all_digit(char *str);
int				pack_win_size(t_cub *cub, char *line);
int				pack_wsize_update_flag(t_cub *cub, char *line, int *flag);
int				check_texture_line(char *line);
int				count_strs(char **strs, int i);
int				pack_path(t_cub *cub, char *line);
int				pack_path_update_flag(t_cub *cub, char *line, int *flag,
					int index);
int				check_rgb_line(char *line);
int				check_rgb_available(char **strs, t_cub *cub);
void			add_color(t_cub *cub);
int				free_for_pack_rgb(char **sub_strs, char **strs, int len,
					int ret);
void			pack_rgb_atoi(char c, t_cub *cub, char **strs);
int				pack_rgb(t_cub *cub, char *line);
int				pack_rgb_update_flag(t_cub *cub, char *line, int *flag,
					int index);
int				free_line_ret_mes(char *line);
int				pack_line_each_info(t_cub *cub, int *flag, char *line,
					int *index);
void			fill_map_space(t_cub *cub);
int				get_conf(t_cub *cub, char *file_name);
void			add_some_pi(t_cub *cub, float base, float height, int i);
void			get_info_sprite(t_cub *cub);
int				close_button_press(t_cub *cub);
int				key_press(int key, t_cub *cub);
int				key_release(int key, t_cub *cub);
int				map_has_wall_at(t_cub *cub, float x, float y);
void			set_new_player_x(t_cub *cub, float *new_player_x);
void			set_new_player_y(t_cub *cub, float *new_player_y);
void			set_new_rotation_angle(t_cub *cub);
void			move(t_cub *cub);
void			reset_sprite_info(t_cub *cub);
int				rendering_loop(t_cub *cub);
int				free_map_ret_error(t_cub *cub, char *str, int ret);
int				get_wall_img_ptr(t_cub *cub);
int				get_sprite_img_ptr(t_cub *cub);
int				setting_img(t_cub *cub);
int				setting_window(t_cub *cub);
void			copy_sprite_first_half(t_cub *cub, int mid, int i);
void			copy_sprite_second_half(t_cub *cub, int right, int i, int j);
void			sort_by_dist(t_cub *cub, int left, int right);
void			mergesort_sprite_structure(t_cub *cub, int left, int right);
void			sort_sprite_structure(t_cub *cub);
void			set_last_sprite(t_cub *cub, int k);
void			count_sprite_num(t_cub *cub);
int				set_sprites(t_cub *cub);
int				check_sprite_info(t_cub *cub);
void			exit_game(t_cub *cub, int ret);

#endif
