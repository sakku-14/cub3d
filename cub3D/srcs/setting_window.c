/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:17:15 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/15 19:45:15 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

int
	setting_window(t_cub *cub)
{
	int x;
	int y;

	x = -1;
	y = -1;
	if (!(cub->window.img_ptr = mlx_new_image(cub->cub_ptr, cub->conf.win_w \
					, cub->conf.win_h)))
	{
		free_cub_map(cub);
		return (FALSE);
	}
	cub->window.data = (int *)mlx_get_data_addr(cub->window.img_ptr \
			, &(cub->window.bpp), &(cub->window.size_l), &(cub->window.endian));
	while (++y < cub->conf.win_h)
	{
		x = -1;
		while (++x < cub->conf.win_w)
		{
			cub->window.data[y * (cub->window.size_l / 4) + x] = 0x000000;
		}
	}
	return (TRUE);
}
