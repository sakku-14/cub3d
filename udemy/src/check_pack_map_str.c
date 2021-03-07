/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pack_map_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:28:27 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/07 13:30:54 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"

int
	check_is_map(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!check_c_in_str(line[i], " 012NSEW"))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int
	pack_map_str(t_cub *cub, char *line)
{
	char	*tmp;
	int		len;

	if (cub->conf.cub_flag[8] == 1)
	{
		if (!(cub->conf.map_str = malloc(sizeof(char))))
		{
			return (error_mes("Error\n could not malloc for map_str\n"\
				, FALSE));
		}
		*(cub->conf.map_str) = '\0';
	}
	cub->conf.cub_flag[8]++;
	len = ft_strlen(line);
	cub->conf.map_x = max_len(cub->conf.map_x, len);
	tmp = cub->conf.map_str;
	cub->conf.map_str = ft_strjoin(cub->conf.map_str, line);
	free_str_safe(tmp);
	tmp = cub->conf.map_str;
	cub->conf.map_str = ft_strjoin(cub->conf.map_str, "\n");
	cub->conf.map_y++;
	free_str_safe(tmp);
	return (TRUE);
}

int
	check_pack_map_str(t_cub *cub, int *flag, char *line)
{
	if ((cub->conf.cub_flag[8] == 0 \
				&& conf_fill_checker(cub) == FALSE) || *flag == 10)
		return (free_line_ret_mes(line));
	if (check_is_map(line) == FALSE)
	{
		free_str_safe(line);
		return (error_mes("Error\n map is not made by map element\n", FALSE));
	}
	*flag = 9;
	cub->conf.cub_flag[8]++;
	if (pack_map_str(cub, line) == FALSE)
	{
		free_str_safe(line);
		return (FALSE);
	}
	free_str_safe(line);
	return (TRUE);
}
