/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:16:59 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/17 09:18:18 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

int
	free_map_ret_error(t_cub *cub, char *str, int ret)
{
	free_cub_map(cub);
	error_mes(str, ret);
	return (ret);
}

int
	get_wall_img_ptr(t_cub *cub)
{
	int width;
	int height;
	int flag;

	width = TEXTURE_WIDTH;
	height = TEXTURE_HEIGHT;
	flag = 0;
	if (!(cub->tex[0].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr, \
		cub->conf.path_so, &width, &height)))
		flag = 1;
	if (!(cub->tex[1].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr, \
		cub->conf.path_no, &width, &height)))
		flag = 1;
	if (!(cub->tex[2].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr, \
		cub->conf.path_we, &width, &height)))
		flag = 1;
	if (!(cub->tex[3].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr, \
		cub->conf.path_ea, &width, &height)))
		flag = 1;
	if (flag == 1)
	{
		return (free_map_ret_error(cub, "Error\n invalid texture file\n", \
			FALSE));
	}
	return (TRUE);
}

int
	get_sprite_img_ptr(t_cub *cub)
{
	int width;
	int height;

	width = TEXTURE_WIDTH;
	height = TEXTURE_HEIGHT;
	if (!(cub->tex[4].img_ptr = mlx_xpm_file_to_image(cub->cub_ptr \
					, cub->conf.path_sp, &width, &height)))
	{
		return (free_map_ret_error(cub, "Error\n invalid texture file\n" \
					, FALSE));
	}
	return (TRUE);
}

int
	setting_img(t_cub *cub)
{
	if (!check_path_available(cub))
	{
		return (free_map_ret_error(cub, "Error\n invalid path of texture\n" \
			, FALSE));
	}
	if (get_wall_img_ptr(cub) == FALSE)
		return (FALSE);
	if (get_sprite_img_ptr(cub) == FALSE)
		return (FALSE);
	cub->tex[0].data = (int *)mlx_get_data_addr(cub->tex[0].img_ptr \
			, &(cub->tex[0].bpp), &(cub->tex[0].size_l), &(cub->tex[0].endian));
	cub->tex[1].data = (int *)mlx_get_data_addr(cub->tex[1].img_ptr \
			, &(cub->tex[1].bpp), &(cub->tex[1].size_l), &(cub->tex[1].endian));
	cub->tex[2].data = (int *)mlx_get_data_addr(cub->tex[2].img_ptr \
			, &(cub->tex[2].bpp), &(cub->tex[2].size_l), &(cub->tex[2].endian));
	cub->tex[3].data = (int *)mlx_get_data_addr(cub->tex[3].img_ptr \
			, &(cub->tex[3].bpp), &(cub->tex[3].size_l), &(cub->tex[3].endian));
	cub->tex[4].data = (int *)mlx_get_data_addr(cub->tex[4].img_ptr \
			, &(cub->tex[4].bpp), &(cub->tex[4].size_l), &(cub->tex[4].endian));
	return (TRUE);
}
