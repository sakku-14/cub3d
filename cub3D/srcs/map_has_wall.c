/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_has_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:15:24 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/15 19:44:59 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

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
