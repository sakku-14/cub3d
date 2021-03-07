/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ray_facing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:46:47 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/07 13:47:06 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

void
	set_ray_facing(t_cub *cub, float ray_angle)
{
	cub->cast.is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	cub->cast.is_ray_facing_up = !cub->cast.is_ray_facing_down;
	cub->cast.is_ray_facing_right = \
		ray_angle < PI / 2 || ray_angle > PI * 3 / 2;
	cub->cast.is_ray_facing_left = !cub->cast.is_ray_facing_right;
}
