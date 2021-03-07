/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:16:22 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/07 11:05:34 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void
	reset_sprite_info(t_cub *cub)
{
	int i;

	i = 0;
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
