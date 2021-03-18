/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_win_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:35:30 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/18 11:12:13 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

int
	get_ray_size(t_cub *cub)
{
	if (!(cub->rays = malloc(sizeof(t_rays) * (cub->conf.win_w + 1))))
		return (FALSE);
	return (TRUE);
}

int
	is_all_digit(char *str)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int
	pack_win_error(int num, char **strs)
{
	if (num != 3)
		return (FALSE);
	if (ft_strlen(strs[0]) != 1)
		return (FALSE);
	if (!is_all_digit(strs[1]) || !is_all_digit(strs[2]))
		return (FALSE);
	return (TRUE);
}

static int
	pack_check_winsize(t_cub *cub)
{
	if (cub->save_flag != 1)
	{
		cub->conf.win_w = cub->conf.win_w > cub->conf.win_max_w ? \
									cub->conf.win_max_w : cub->conf.win_w;
		cub->conf.win_h = cub->conf.win_h > cub->conf.win_max_h ? \
									cub->conf.win_max_h : cub->conf.win_h;
	}
	else
	{
		if (cub->conf.win_w > 5000 || cub->conf.win_h > 5000)
			return (FALSE);
	}
	return (TRUE);
}

int
	pack_win_size(t_cub *cub, char *line)
{
	char	**strs;
	int		num;

	strs = ft_split(line, ' ');
	num = 0;
	while (strs[num])
		num++;
	if (pack_win_error(num, strs) == FALSE)
		return (free_strs(strs, num, FALSE));
	cub->conf.win_w = ft_atoi(strs[1]);
	cub->conf.win_h = ft_atoi(strs[2]);
	if (cub->conf.win_w <= 0 || cub->conf.win_h <= 0)
		return (free_strs(strs, num, FALSE));
	if (pack_check_winsize(cub) == FALSE)
		return (free_strs(strs, num, FALSE));
	if (get_ray_size(cub) == FALSE)
		return (free_strs(strs, num, FALSE));
	free_str_safe(line);
	return (free_strs(strs, num, TRUE));
}
