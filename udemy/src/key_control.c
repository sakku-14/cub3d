/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:15:00 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/05 19:15:01 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

int
	close_button_press(t_cub *cub)
{
	mlx_destroy_window(cub->cub_ptr, cub->win);
	free_cub_map(cub);
	free_cub(cub, TRUE);
	exit(0);
	return (TRUE);
}

int
	key_press(int key, t_cub *cub)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_window(cub->cub_ptr, cub->win);
		free_cub_map(cub);
		free_cub(cub, TRUE);
		exit(0);
	}
	if (key == KEY_W)
		cub->player.walk_direction = +1;
	if (key == KEY_S)
		cub->player.walk_direction = -1;
	if (key == KEY_D)
		cub->player.side_direction = +1;
	if (key == KEY_A)
		cub->player.side_direction = -1;
	if (key == KEY_RIGHT)
		cub->player.turn_direction = +1;
	if (key == KEY_LEFT)
		cub->player.turn_direction = -1;
	return (TRUE);
}

int
	key_release(int key, t_cub *cub)
{
	if (key == KEY_W)
		cub->player.walk_direction = 0;
	if (key == KEY_S)
		cub->player.walk_direction = 0;
	if (key == KEY_D)
		cub->player.side_direction = 0;
	if (key == KEY_A)
		cub->player.side_direction = 0;
	if (key == KEY_RIGHT)
		cub->player.turn_direction = 0;
	if (key == KEY_LEFT)
		cub->player.turn_direction = 0;
	return (TRUE);
}
