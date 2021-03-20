/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:14:31 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/20 17:48:42 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

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
	int		i;
	float	base;
	float	height;

	i = 0;
	while (i < cub->sprite_num)
	{
		if (cub->sprite[i].visible == 1)
		{
			base = (cub->sprite[i].sprite_x + 0.5) \
					* TILE_SIZE - cub->conf.pl_x;
			height = (cub->sprite[i].sprite_y + 0.5) \
					* TILE_SIZE - cub->conf.pl_y;
			cub->sprite[i].distance = dist_between_points(\
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
