/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_set_vert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:43:15 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/07 15:37:38 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void
	init_vert_wall_hit(t_cub *cub)
{
	cub->cast.found_vert_wall_hit = FALSE;
	cub->cast.vert_wall_hit_x = 0;
	cub->cast.vert_wall_hit_y = 0;
	cub->cast.vert_wall_content = '\0';
}

void
	set_vert_intercept_step(t_cub *cub, float ray_angle)
{
	cub->cast.x_intercept = floor(cub->conf.pl_x / TILE_SIZE) * TILE_SIZE;
	cub->cast.x_intercept += cub->cast.is_ray_facing_right ? TILE_SIZE : 0;
	cub->cast.y_intercept = \
		cub->conf.pl_y + (cub->cast.x_intercept - cub->conf.pl_x) \
		* tan(ray_angle);
	cub->cast.x_step = TILE_SIZE;
	cub->cast.x_step *= cub->cast.is_ray_facing_left ? -1 : 1;
	cub->cast.y_step = TILE_SIZE * tan(ray_angle);
	cub->cast.y_step *= \
		(cub->cast.is_ray_facing_up && cub->cast.y_step > 0) ? -1 : 1;
	cub->cast.y_step *= \
		(cub->cast.is_ray_facing_down && cub->cast.y_step < 0) ? -1 : 1;
}

void
	set_vert_next_touch(t_cub *cub)
{
	cub->cast.next_vert_touch_x = cub->cast.x_intercept;
	cub->cast.next_vert_touch_y = cub->cast.y_intercept;
}

int
	check_vert_wall_set(t_cub *cub, float x_to_check, float y_to_check)
{
	if (map_has_wall_at(cub, x_to_check, y_to_check))
	{
		cub->cast.vert_wall_hit_x = cub->cast.next_vert_touch_x;
		cub->cast.vert_wall_hit_y = cub->cast.next_vert_touch_y;
		if (!(\
			(int)floor(y_to_check / TILE_SIZE) < 0 \
			|| (int)floor(x_to_check / TILE_SIZE) < 0 \
			|| (int)floor(y_to_check / TILE_SIZE) >= cub->conf.map_y \
			|| (int)floor(x_to_check / TILE_SIZE) >= cub->conf.map_x))
			cub->cast.vert_wall_content = \
				(cub->conf.map)[(int)floor(y_to_check / TILE_SIZE)]\
				[(int)floor(x_to_check / TILE_SIZE)];
		else
			cub->cast.vert_wall_content = '1';
		cub->cast.found_vert_wall_hit = TRUE;
		return (TRUE);
	}
	else
	{
		cub->cast.next_vert_touch_x += cub->cast.x_step;
		cub->cast.next_vert_touch_y += cub->cast.y_step;
		return (FALSE);
	}
}

void
	set_vert_wall_hit(t_cub *cub)
{
	float x_to_check;
	float y_to_check;

	while (cub->cast.next_vert_touch_x >= 0 \
			&& cub->cast.next_vert_touch_x <= cub->conf.map_x * TILE_SIZE \
			&& cub->cast.next_vert_touch_y >= 0 \
			&& cub->cast.next_vert_touch_y <= cub->conf.map_y * TILE_SIZE)
	{
		x_to_check = cub->cast.next_vert_touch_x \
			+ (cub->cast.is_ray_facing_left ? -1 : 0);
		y_to_check = cub->cast.next_vert_touch_y;
		map_has_sprite_at(x_to_check, y_to_check, cub);
		if (check_vert_wall_set(cub, x_to_check, y_to_check) == TRUE)
			break ;
	}
}
