/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_update_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:33:41 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 12:38:34 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

int
	pack_wsize_update_flag(t_cub *cub, char *line, int *flag)
{
	if (pack_win_size(cub, line) == FALSE)
		return (free_line_ret_mes(line));
	(*flag)++;
	cub->conf.cub_flag[0] = 1;
	return (TRUE);
}

int
	pack_path_update_flag(t_cub *cub, char *line, int *flag, int index)
{
	if (pack_path(cub, line) == FALSE)
		return (free_line_ret_mes(line));
	(*flag)++;
	cub->conf.cub_flag[index] = 1;
	return (TRUE);
}

int
	pack_rgb_update_flag(t_cub *cub, char *line, int *flag, int index)
{
	if (pack_rgb(cub, line) == FALSE)
		return (free_line_ret_mes(line));
	(*flag)++;
	cub->conf.cub_flag[index] = 1;
	return (TRUE);
}
