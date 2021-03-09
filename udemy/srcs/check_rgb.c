/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:38:01 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 12:36:19 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

int
	check_rgb_line(char *line)
{
	if (ft_strnstr(line, "F", 1))
		return (6);
	else if (ft_strnstr(line, "C", 1))
		return (7);
	return (FALSE);
}

int
	check_rgb_available(char **strs, t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (strs[i][j] != '\0')
		{
			if (ft_isdigit(strs[i][j]))
				j++;
			else
				return (FALSE);
		}
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (cub->conf.floor_colors[i] < 0 || cub->conf.floor_colors[i] > 255 \
			|| cub->conf.ceil_colors[i] < 0 || cub->conf.ceil_colors[i] > 255)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
