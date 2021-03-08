/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen3d_describe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:06:54 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/07 13:11:37 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

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
