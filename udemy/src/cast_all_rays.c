/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:51:07 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/07 15:38:24 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void
	set_hit_distance(t_cub *cub)
{
	cub->cast.horz_hit_distance = cub->cast.found_horz_wall_hit
		? dist_between_points(cub->conf.pl_x, cub->conf.pl_y\
			, cub->cast.horz_wall_hit_x, cub->cast.horz_wall_hit_y)
		: FLT_MAX;
	cub->cast.vert_hit_distance = cub->cast.found_vert_wall_hit
		? dist_between_points(cub->conf.pl_x, cub->conf.pl_y\
			, cub->cast.vert_wall_hit_x, cub->cast.vert_wall_hit_y)
		: FLT_MAX;
}

void
	set_ray_info(t_cub *cub, int strip_id, float ray_angle)
{
	if (cub->cast.vert_hit_distance < cub->cast.horz_hit_distance)
	{
		cub->rays[strip_id].distance = cub->cast.vert_hit_distance;
		cub->rays[strip_id].wall_hit_x = cub->cast.vert_wall_hit_x;
		cub->rays[strip_id].wall_hit_y = cub->cast.vert_wall_hit_y;
		cub->rays[strip_id].wall_hit_content = cub->cast.vert_wall_content;
		cub->rays[strip_id].was_hit_vertical = TRUE;
	}
	else
	{
		cub->rays[strip_id].distance = cub->cast.horz_hit_distance;
		cub->rays[strip_id].wall_hit_x = cub->cast.horz_wall_hit_x;
		cub->rays[strip_id].wall_hit_y = cub->cast.horz_wall_hit_y;
		cub->rays[strip_id].wall_hit_content = cub->cast.horz_wall_content;
		cub->rays[strip_id].was_hit_vertical = FALSE;
	}
	cub->rays[strip_id].ray_angle = ray_angle;
	cub->rays[strip_id].is_ray_facing_down = cub->cast.is_ray_facing_down;
	cub->rays[strip_id].is_ray_facing_up = cub->cast.is_ray_facing_up;
	cub->rays[strip_id].is_ray_facing_left = cub->cast.is_ray_facing_left;
	cub->rays[strip_id].is_ray_facing_right = cub->cast.is_ray_facing_right;
}

void
	cast_ray(float ray_angle, int strip_id, t_cub *cub)
{
	ray_angle = normalize_angle(ray_angle);
	set_ray_facing(cub, ray_angle);
	init_horz_wall_hit(cub);
	set_horz_intercept_step(cub, ray_angle);
	set_horz_next_touch(cub);
	set_horz_wall_hit(cub);
	init_vert_wall_hit(cub);
	set_vert_intercept_step(cub, ray_angle);
	set_vert_next_touch(cub);
	set_vert_wall_hit(cub);
	set_hit_distance(cub);
	set_ray_info(cub, strip_id, ray_angle);
}

void
	cast_all_rays(t_cub *cub)
{
	int		strip_id;
	float	ray_angle;

	strip_id = 0;
	ray_angle = cub->player.rotation_angle - (FOV_ANGLE / 2);
	while (strip_id < cub->conf.win_w)
	{
		cast_ray(ray_angle, strip_id, cub);
		strip_id++;
		ray_angle += FOV_ANGLE / cub->conf.win_w;
	}
}
