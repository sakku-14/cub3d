/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:09:51 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 12:37:19 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

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
