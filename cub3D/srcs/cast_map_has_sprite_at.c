/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_map_has_sprite_at.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:48:08 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/15 19:44:26 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

int
	search_sprite_index(int x, int y, t_cub *cub)
{
	int i;

	i = 0;
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
