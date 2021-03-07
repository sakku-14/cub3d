/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen3d_set_sprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:09:08 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/07 13:11:55 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

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
		+ cub->sprite[j].texture_offset_x] & 0xffffff) != 0)
	{
		cub->window.data[((cub->window.size_l / 4) * y) + x] = \
			cub->tex[4].data[((cub->tex[4].size_l / 4) \
			* cub->sprite[j].texture_offset_y) \
			+ cub->sprite[j].texture_offset_x];
	}
}
