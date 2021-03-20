/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:14:11 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/20 17:48:42 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	fill_map_space(t_cub *cub)
{
	int		index;
	char	*tmp;

	index = 0;
	while (index < cub->conf.map_y)
	{
		while ((int)ft_strlen((cub->conf.map)[index]) < cub->conf.map_x)
		{
			tmp = cub->conf.map[index];
			(cub->conf.map)[index] = ft_strjoin((cub->conf.map)[index], " ");
			free_str_safe(tmp);
		}
		index++;
	}
}

int
	get_conf(t_cub *cub, char *file_name)
{
	int		fd;
	int		res;
	int		flag;
	int		index;
	char	*line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (error_mes("Error\n invalid fd\n", FALSE));
	flag = 0;
	while ((res = get_next_line(fd, &line)))
	{
		if (res == -1)
			return (error_mes("Error\n some error while gnl working\n", FALSE));
		if (pack_line_each_info(cub, &flag, line, &index) == FALSE)
			return (FALSE);
	}
	cub->conf.map = ft_split(cub->conf.map_str, '\n');
	fill_map_space(cub);
	free_str_safe(line);
	return (TRUE);
}
