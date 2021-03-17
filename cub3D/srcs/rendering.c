/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:16:22 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/15 19:45:11 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

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
	reset_sprite_info(cub);
	return (TRUE);
}
