/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pack_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:31:38 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/07 13:32:17 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

int
	conf_fill_checker(t_cub *cub)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (cub->conf.cub_flag[i++] == 0)
			return (FALSE);
	}
	return (TRUE);
}

int
	check_c_in_str(char c, char *str)
{
	int len;
	int i;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int
	max_len(int x, int y)
{
	if (x > y)
		return (x);
	else
		return (y);
}
