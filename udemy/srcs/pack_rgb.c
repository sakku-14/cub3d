/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_rgb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:37:18 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/11 11:19:33 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	add_color(t_cub *cub)
{
	cub->conf.floor_c = cub->conf.floor_colors[0];
	cub->conf.floor_c = cub->conf.floor_c << 8;
	cub->conf.floor_c = cub->conf.floor_c | cub->conf.floor_colors[1];
	cub->conf.floor_c = cub->conf.floor_c << 8;
	cub->conf.floor_c = cub->conf.floor_c | cub->conf.floor_colors[2];
	cub->conf.ceil_c = cub->conf.ceil_colors[0];
	cub->conf.ceil_c = cub->conf.ceil_c << 8;
	cub->conf.ceil_c = cub->conf.ceil_c | cub->conf.ceil_colors[1];
	cub->conf.ceil_c = cub->conf.ceil_c << 8;
	cub->conf.ceil_c = cub->conf.ceil_c | cub->conf.ceil_colors[2];
}

int
	free_for_pack_rgb(char **sub_strs, char **strs, int len, int ret)
{
	free_strs(sub_strs, 2, 0);
	return (free_strs(strs, len, ret));
}

void
	pack_rgb_atoi(char c, t_cub *cub, char **strs)
{
	if (c == 'F')
	{
		cub->conf.floor_colors[0] = ft_atoi(strs[0]);
		cub->conf.floor_colors[1] = ft_atoi(strs[1]);
		cub->conf.floor_colors[2] = ft_atoi(strs[2]);
	}
	if (c == 'C')
	{
		cub->conf.ceil_colors[0] = ft_atoi(strs[0]);
		cub->conf.ceil_colors[1] = ft_atoi(strs[1]);
		cub->conf.ceil_colors[2] = ft_atoi(strs[2]);
	}
}

int
	pack_rgb(t_cub *cub, char *line)
{
	char	**sub_strs;
	char	**strs;

	sub_strs = ft_split(line, ' ');
	if (count_strs(sub_strs, 0) != 2)
		return (free_strs(sub_strs, count_strs(sub_strs, 0), FALSE));
	strs = ft_split(sub_strs[1], ',');
	if (count_strs(strs, 0) != 3)
		return (free_for_pack_rgb(sub_strs, strs, count_strs(strs, 0), FALSE));
	if (ft_strnstr(sub_strs[0], "F", 1) && ft_strlen(sub_strs[0]) == 1)
		pack_rgb_atoi('F', cub, strs);
	else if (ft_strnstr(sub_strs[0], "C", 1) && ft_strlen(sub_strs[0]) == 1)
		pack_rgb_atoi('C', cub, strs);
	else
		return (free_for_pack_rgb(sub_strs, strs, 3, FALSE));
	if (check_rgb_available(strs, cub) == FALSE)
		return (free_for_pack_rgb(sub_strs, strs, 3, FALSE));
	add_color(cub);
	free_str_safe(line);
	return (free_for_pack_rgb(sub_strs, strs, 3, TRUE));
}
