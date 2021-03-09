/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_line_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:19:15 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 17:38:42 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	pass_empty_line(char *line, int *flag)
{
	free_str_safe(line);
	if (*flag == 9)
		*flag = 10;
}

int
	free_line_ret_mes(char *line)
{
	free_str_safe(line);
	return (error_mes("Error\n invalid configure\n", FALSE));
}

int
	pack_line_each_info(t_cub *cub, int *flag, char *line, int *index)
{
	if (!*line)
		pass_empty_line(line, flag);
	else if (*flag >= 8)
	{
		if (check_pack_map_str(cub, flag, line) == FALSE)
			return (FALSE);
	}
	else if (ft_strnstr(line, "R", 1))
	{
		if (pack_wsize_update_flag(cub, line, flag) == FALSE)
			return (FALSE);
	}
	else if ((*index = check_texture_line(line)) != FALSE)
	{
		if (pack_path_update_flag(cub, line, flag, *index) == FALSE)
			return (FALSE);
	}
	else if ((*index = check_rgb_line(line)) != FALSE)
	{
		if (pack_rgb_update_flag(cub, line, flag, *index) == FALSE)
			return (FALSE);
	}
	else
		return (free_line_ret_mes(line));
	return (TRUE);
}
