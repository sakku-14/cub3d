/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:06:41 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/05 19:06:43 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

/*
void
	put_line(t_cub *cub)
{
	int r = 0;
	while (r < 150 / MINIMAP_SCALE_FACTOR)
	{
		mlx_pixel_put(
				cub->cub_ptr,
				cub->win,
				((cub->conf.pl_x + r * cos(cub->player.rotation_angle)) * cub->conf.win_w)
				/ (cub->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR),
				((cub->conf.pl_y + r * sin(cub->player.rotation_angle)) * cub->conf.win_h)
				/ (cub->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR),
				0x00FF00
				);
		r++;
	}
}
*/
/*
int
	setting_ray_point(t_cub *cub)
{
	int x = -1;
	int y = -1;
	int i = 0;

	while (i < cub->conf.win_w)
	{
		if (!(cub->rays[i].img_ptr = mlx_new_image(cub->cub_ptr, 20 / MINIMAP_SCALE_FACTOR, 20 / MINIMAP_SCALE_FACTOR)))
		{
			free_cub_map(cub);
			return (error_mes("Error\n false cub_new_image for ray image\n", FALSE));
		}
		cub->rays[i].data = (int *)mlx_get_data_addr(cub->rays[i].img_ptr, &(cub->rays[i].bpp), &(cub->rays[i].size_l), &(cub->rays[i].endian));
		y = -1;
		while (++y < 20 / MINIMAP_SCALE_FACTOR)
		{
			x = -1;
			while (++x < 20 / MINIMAP_SCALE_FACTOR)
			{
				cub->rays[i].data[y * (cub->rays[i].size_l / 4) + x] = 0xff0000;
			}
		}
		i++;
	}
	return (TRUE);
}
*/

/*
void
	put_rays(t_cub *cub)
{
	int i = 0;

	while (i < cub->conf.win_w)
	{
		// all ray put func from here
		r = 0;
		while (r < cub->rays[i].distance / MINIMAP_SCALE_FACTOR)
		{
			mlx_pixel_put(cub->cub_ptr, cub->win, cub->conf.pl_x / MINIMAP_SCALE_FACTOR + (r * cos(cub->rays[i].ray_angle)), cub->conf.pl_y / MINIMAP_SCALE_FACTOR + (r * sin(cub->rays[i].ray_angle)), 0x00FF00);
			r++;
		}
		// till here
		mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->rays[i].img_ptr, (cub->rays[i].wall_hit_x * cub->conf.win_w) / (cub->conf.map_x * TILE_SIZE * MINIMAP_SCALE_FACTOR), (cub->rays[i].wall_hit_y * cub->conf.win_h) / (cub->conf.map_y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
		i++;
	}
}
*/
/*
int
	setting_map(t_cub *cub)
{
	int x = -1;
	int y = -1;

	//TODO: leak check again
	if(!(cub->map.img_ptr = mlx_new_image(cub->cub_ptr, cub->conf.win_w / MINIMAP_SCALE_FACTOR, cub->conf.win_h / MINIMAP_SCALE_FACTOR)))
	{
		free_cub_map(cub);
		return (error_mes("Error\n false cub_new_image for map image\n", FALSE));
	}
	cub->map.data = (int *)mlx_get_data_addr(cub->map.img_ptr, &(cub->map.bpp), &(cub->map.size_l), &(cub->map.endian));
	while (++y < cub->conf.win_h / MINIMAP_SCALE_FACTOR)
	{
		x = -1;
		while (++x < cub->conf.win_w / MINIMAP_SCALE_FACTOR)
		{
			cub->map.tile_x = (x * cub->conf.map_x) / (cub->conf.win_w / MINIMAP_SCALE_FACTOR);
			cub->map.tile_y = (y * cub->conf.map_y) / (cub->conf.win_h / MINIMAP_SCALE_FACTOR);
			if ((cub->conf.map)[cub->map.tile_y][cub->map.tile_x] == '0')
				cub->map.data[y * (cub->map.size_l / 4) + x] = 0x020202;
			else if ((cub->conf.map)[cub->map.tile_y][cub->map.tile_x] == '1')
				cub->map.data[y * (cub->map.size_l / 4) + x] = 0xffffff;
		}
	}
	return (TRUE);
}
*/
/*
int
	setting_player(t_cub *cub)
{
	int x = -1;
	int y = -1;

	//TODO: leak check again
	if (!(cub->player.img_ptr = mlx_new_image(cub->cub_ptr, cub->player.width, cub->player.height)))
	{
		free_cub_map(cub);
		return (error_mes("Error\n false cub_new_image for player image\n", FALSE));
	}
	cub->player.data = (int *)mlx_get_data_addr(cub->player.img_ptr, &(cub->player.bpp), &(cub->player.size_l), &(cub->player.endian));
	while (++y < cub->player.height)
	{
		x = -1;
		while (++x < cub->player.width)
		{
			cub->player.data[y * (cub->player.size_l / 4) + x] = 0xFFFF00;
		}
	}
	return (TRUE);
}
*/
/*
void
	print_map(char *map_p, int y, int x)
{
	int i = 0;
	int j = 0;

	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%c", map_p[i * x + j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}
*/
