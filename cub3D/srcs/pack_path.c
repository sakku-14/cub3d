/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 13:36:24 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/20 17:48:47 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

int
	check_texture_line(char *line)
{
	if (ft_strnstr(line, "NO", 2))
		return (1);
	else if (ft_strnstr(line, "SO", 2))
		return (2);
	else if (ft_strnstr(line, "EA", 2))
		return (3);
	else if (ft_strnstr(line, "WE", 2))
		return (4);
	else if (ft_strnstr(line, "S", 1))
		return (5);
	return (FALSE);
}

int
	count_strs(char **strs, int i)
{
	int counter;

	counter = i;
	if (!strs || !strs[counter])
		return (counter);
	while (strs[counter])
		counter++;
	return (counter);
}

int
	pack_path(t_cub *cub, char *line)
{
	char	**strs;
	int		len;

	strs = ft_split(line, ' ');
	if (count_strs(strs, 0) != 2)
		return (free_strs(strs, count_strs(strs, 0), FALSE));
	if (ft_strlen(strs[0]) != 2 \
			&& (ft_strlen(strs[0]) != 1 && ft_strncmp(strs[0], "S", 1)))
		return (free_strs(strs, 2, FALSE));
	len = ft_strlen(strs[1]);
	if (strs[1])
	{
		if (ft_strnstr(strs[0], "NO", 2))
			cub->conf.path_no = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "SO", 2))
			cub->conf.path_so = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "EA", 2))
			cub->conf.path_ea = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "WE", 2))
			cub->conf.path_we = ft_substr(strs[1], 0, len);
		else if (ft_strnstr(strs[0], "S", 1))
			cub->conf.path_sp = ft_substr(strs[1], 0, len);
	}
	free_str_safe(line);
	return (free_strs(strs, 2, TRUE));
}
