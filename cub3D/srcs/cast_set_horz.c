/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_set_horz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:42:33 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/15 19:44:28 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	init_horz_wall_hit(t_cub *cub)
{
	cub->cast.found_horz_wall_hit = FALSE;
	cub->cast.horz_wall_hit_x = 0;
	cub->cast.horz_wall_hit_y = 0;
	cub->cast.horz_wall_content = '\0';
}

void
	set_horz_intercept_step(t_cub *cub, float ray_angle)
{
	cub->cast.y_intercept = floor(cub->conf.pl_y / TILE_SIZE) * TILE_SIZE;
	cub->cast.y_intercept += cub->cast.is_ray_facing_down ? TILE_SIZE : 0;
	cub->cast.x_intercept = \
		cub->conf.pl_x + (cub->cast.y_intercept - cub->conf.pl_y) \
		/ tan(ray_angle);
	cub->cast.y_step = TILE_SIZE;
	cub->cast.y_step *= cub->cast.is_ray_facing_up ? -1 : 1;
	cub->cast.x_step = TILE_SIZE / tan(ray_angle);
	cub->cast.x_step *= \
		(cub->cast.is_ray_facing_left && cub->cast.x_step > 0) ? -1 : 1;
	cub->cast.x_step *= \
		(cub->cast.is_ray_facing_right && cub->cast.x_step < 0) ? -1 : 1;
}

void
	set_horz_next_touch(t_cub *cub)
{
	cub->cast.next_horz_touch_x = cub->cast.x_intercept;
	cub->cast.next_horz_touch_y = cub->cast.y_intercept;
}

int
	check_horz_wall_set(t_cub *cub, float x_to_check, float y_to_check)
{
	if (map_has_wall_at(cub, x_to_check, y_to_check))
	{
		cub->cast.horz_wall_hit_x = cub->cast.next_horz_touch_x;
		cub->cast.horz_wall_hit_y = cub->cast.next_horz_touch_y;
		if (!((int)floor(y_to_check / TILE_SIZE) < 0 \
			|| (int)floor(x_to_check / TILE_SIZE) < 0 \
			|| (int)floor(y_to_check / TILE_SIZE) >= cub->conf.map_y \
			|| (int)floor(x_to_check / TILE_SIZE) >= cub->conf.map_x))
			cub->cast.horz_wall_content = \
				(cub->conf.map)[(int)floor(y_to_check / TILE_SIZE)]\
				[(int)floor(x_to_check / TILE_SIZE)];
		else
			cub->cast.horz_wall_content = '1';
		cub->cast.found_horz_wall_hit = TRUE;
		return (TRUE);
	}
	else
	{
		cub->cast.next_horz_touch_x += cub->cast.x_step;
		cub->cast.next_horz_touch_y += cub->cast.y_step;
		return (FALSE);
	}
}

void
	set_horz_wall_hit(t_cub *cub)
{
	float x_to_check;
	float y_to_check;

	while (cub->cast.next_horz_touch_x >= 0 \
			&& cub->cast.next_horz_touch_x <= cub->conf.map_x * TILE_SIZE \
			&& cub->cast.next_horz_touch_y >= 0 \
			&& cub->cast.next_horz_touch_y <= cub->conf.map_y * TILE_SIZE)
	{
		x_to_check = cub->cast.next_horz_touch_x;
		y_to_check = cub->cast.next_horz_touch_y \
			+ (cub->cast.is_ray_facing_up ? -1 : 0);
		map_has_sprite_at(x_to_check, y_to_check, cub);
		if (check_horz_wall_set(cub, x_to_check, y_to_check) == TRUE)
			break ;
	}
}
