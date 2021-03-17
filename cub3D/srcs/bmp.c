/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 15:49:15 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/17 10:55:10 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	make_img(t_cub *cub, int fd)
{
	int	x;
	int	y;
	int	color;

	y = cub->conf.win_h - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < cub->conf.win_w)
		{
			color = cub->window.data[((cub->window.size_l / 4) * y) + x];
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

void
	make_header(t_cub *cub, int fd, unsigned int header_size \
			, unsigned int img_size)
{
	unsigned int	file_header_size;
	unsigned int	info_header_size;
	unsigned int	bmp_size;
	unsigned int	plane;

	file_header_size = write(fd, "BM", 2);
	bmp_size = header_size + img_size;
	file_header_size += write(fd, &bmp_size, 4);
	file_header_size += write(fd, "\0\0\0\0", 4);
	file_header_size += write(fd, &header_size, 4);
	info_header_size = header_size - file_header_size;
	write(fd, &info_header_size, 4);
	write(fd, &(cub->conf.win_w), 4);
	write(fd, &(cub->conf.win_h), 4);
	plane = 1;
	write(fd, &plane, 2);
	write(fd, &(cub->window.bpp), 2);
	write(fd, "\0\0\0\0", 4);
	write(fd, &img_size, 4);
	write(fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

int
	rendering_for_bmp(t_cub *cub)
{
	move(cub);
	cast_all_rays(cub);
	get_info_sprite(cub);
	sort_sprite_structure(cub);
	generate_3d_projection(cub);
	mlx_put_image_to_window(cub->cub_ptr, cub->win, cub->window.img_ptr, 0, 0);
	return (TRUE);
}

static int
	check_size(t_cub *cub)
{
	if (cub->conf.win_w > 5000 || cub->conf.win_h > 5000)
	{
		return (error_mes("Error\n huge image size\n", FALSE));
	}
	return (TRUE);
}

int
	create_bmp(t_cub *cub)
{
	int				fd;
	unsigned int	img_size;
	unsigned int	header_size;

	rendering_for_bmp(cub);
	if (check_size(cub) == FALSE)
	{
		free_cub_map(cub);
		return (FALSE);
	}
	if ((fd = open("image.bmp", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
	{
		close(fd);
		free_cub_map(cub);
		return (FALSE);
	}
	img_size = (unsigned int)(cub->conf.win_w * cub->conf.win_h) \
		* (cub->window.bpp / 8);
	header_size = 54;
	make_header(cub, fd, header_size, img_size);
	make_img(cub, fd);
	free_cub_map(cub);
	free_cub(cub, TRUE);
	exit(0);
}
