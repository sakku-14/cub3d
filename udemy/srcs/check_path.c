/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:06:23 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 12:36:11 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

int
	check_path_available(t_cub *cub)
{
	int fd[5];
	int i;

	fd[0] = open(cub->conf.path_no, O_RDONLY);
	close(fd[0]);
	fd[1] = open(cub->conf.path_so, O_RDONLY);
	close(fd[1]);
	fd[2] = open(cub->conf.path_ea, O_RDONLY);
	close(fd[2]);
	fd[3] = open(cub->conf.path_we, O_RDONLY);
	close(fd[3]);
	fd[4] = open(cub->conf.path_sp, O_RDONLY);
	close(fd[4]);
	i = 0;
	while (i < 5)
	{
		if (fd[i] == -1)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
