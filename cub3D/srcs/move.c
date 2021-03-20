/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:16:02 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/20 17:48:45 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	set_new_player_x(t_cub *cub, float *new_player_x)
{
	if (cub->player.side_direction == 1)
		*new_player_x = cub->conf.pl_x \
			+ cos(cub->player.rotation_angle + PI / 2) * cub->player.walk_speed;
	else if (cub->player.side_direction == -1)
		*new_player_x = cub->conf.pl_x \
			- cos(cub->player.rotation_angle + PI / 2) * cub->player.walk_speed;
	else if (cub->player.walk_direction == 1)
		*new_player_x = cub->conf.pl_x \
			+ cos(cub->player.rotation_angle) * cub->player.walk_speed;
	else if (cub->player.walk_direction == -1)
		*new_player_x = cub->conf.pl_x \
			- cos(cub->player.rotation_angle) * cub->player.walk_speed;
}

void
	set_new_player_y(t_cub *cub, float *new_player_y)
{
	if (cub->player.side_direction == 1)
		*new_player_y = cub->conf.pl_y \
			+ sin(cub->player.rotation_angle + PI / 2) * cub->player.walk_speed;
	else if (cub->player.side_direction == -1)
		*new_player_y = cub->conf.pl_y \
			- sin(cub->player.rotation_angle + PI / 2) * cub->player.walk_speed;
	else if (cub->player.walk_direction == 1)
		*new_player_y = cub->conf.pl_y \
			+ sin(cub->player.rotation_angle) * cub->player.walk_speed;
	else if (cub->player.walk_direction == -1)
		*new_player_y = cub->conf.pl_y \
			- sin(cub->player.rotation_angle) * cub->player.walk_speed;
}

void
	set_new_rotation_angle(t_cub *cub)
{
	if (cub->player.turn_direction == 1)
		cub->player.rotation_angle += 1 * cub->player.turn_speed;
	else if (cub->player.turn_direction == -1)
		cub->player.rotation_angle -= 1 * cub->player.turn_speed;
}

void
	move(t_cub *cub)
{
	float new_player_x;
	float new_player_y;

	new_player_x = cub->conf.pl_x;
	new_player_y = cub->conf.pl_y;
	set_new_player_x(cub, &new_player_x);
	set_new_player_y(cub, &new_player_y);
	set_new_rotation_angle(cub);
	if (!map_has_wall_at(cub, new_player_x, new_player_y))
	{
		cub->conf.pl_x = new_player_x;
		cub->conf.pl_y = new_player_y;
	}
}
