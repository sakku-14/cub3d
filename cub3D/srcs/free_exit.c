/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:08:05 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/20 17:48:38 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	free_str_safe(char *str)
{
	free(str);
	str = NULL;
}

int
	free_strs(char **strs, int num, int ret)
{
	while (--num >= 0)
	{
		free_str_safe(strs[num]);
		if (num == 0)
			break ;
	}
	free(strs);
	strs = NULL;
	return (ret);
}

void
	free_cub_map(t_cub *cub)
{
	int i;

	i = cub->conf.map_y;
	while (--i >= 0)
	{
		free_str_safe(cub->conf.map[i]);
		if (i == 0)
			break ;
	}
	free(cub->conf.map);
	cub->conf.map = NULL;
}

void
	free_rays(t_cub *cub)
{
	free(cub->rays);
	cub->rays = NULL;
}

int
	free_cub(t_cub *cub, int ret)
{
	if (cub->conf.cub_flag[0] == 1)
		free_rays(cub);
	if (cub->conf.cub_flag[1])
		free(cub->conf.path_no);
	if (cub->conf.cub_flag[2])
		free(cub->conf.path_so);
	if (cub->conf.cub_flag[3])
		free(cub->conf.path_ea);
	if (cub->conf.cub_flag[4])
		free(cub->conf.path_we);
	if (cub->conf.cub_flag[5])
		free(cub->conf.path_sp);
	if (cub->conf.cub_flag[8])
		free(cub->conf.map_str);
	return (ret);
}
