/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_conf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:07:20 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 12:36:51 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	cub_conf(t_cub *cub)
{
	cub->conf.pl_x = (cub->conf.pl_x + 0.501) * TILE_SIZE;
	cub->conf.pl_y = (cub->conf.pl_y + 0.501) * TILE_SIZE;
	cub->player.width = 4;
	cub->player.height = 4;
	cub->player.walk_speed = 3;
	cub->player.turn_speed = 4 * (PI / 180);
}
