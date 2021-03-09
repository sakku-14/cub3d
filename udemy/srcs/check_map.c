/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:06:10 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 12:34:43 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	check_fill(char *map_p, int p_y, int p_x, t_cub *cub)
{
	if (map_p[p_y * (cub->conf.map_x + 2) + p_x] == 'p' \
			|| map_p[p_y * (cub->conf.map_x + 2) + p_x] == '1' \
			|| map_p[p_y * (cub->conf.map_x + 2) + p_x] == '3' \
			|| cub->conf.map_check_flag == 1)
		return ;
	if (map_p[p_y * (cub->conf.map_x + 2) + p_x] == 'X')
	{
		cub->conf.map_check_flag = 1;
		return ;
	}
	if (map_p[p_y * (cub->conf.map_x + 2) + p_x] == '0' \
			|| map_p[p_y * (cub->conf.map_x + 2) + p_x] == 's')
		map_p[p_y * (cub->conf.map_x + 2) + p_x] = 'p';
	if (map_p[p_y * (cub->conf.map_x + 2) + p_x] == '2')
		map_p[p_y * (cub->conf.map_x + 2) + p_x] = '3';
	check_fill(map_p, p_y - 1, p_x, cub);
	check_fill(map_p, p_y, p_x + 1, cub);
	check_fill(map_p, p_y + 1, p_x, cub);
	check_fill(map_p, p_y, p_x - 1, cub);
}

int
	check_player_exist(char spot, t_cub *cub)
{
	if (spot == 'N' || spot == 'S' || spot == 'E' || spot == 'W')
	{
		if (spot == 'N')
			cub->player.rotation_angle = 270 * (PI / 180);
		else if (spot == 'S')
			cub->player.rotation_angle = 90 * (PI / 180);
		else if (spot == 'E')
			cub->player.rotation_angle = 0 * (PI / 180);
		else if (spot == 'W')
			cub->player.rotation_angle = 180 * (PI / 180);
		cub->conf.pl_counter++;
		return (TRUE);
	}
	return (FALSE);
}

int
	pick_player_pl(char *cont_p, int *player_y, int *player_x, t_cub *cub)
{
	int i;
	int j;
	int x;

	x = cub->conf.map_x + 2;
	i = 0;
	while (i < cub->conf.map_y + 2)
	{
		j = 0;
		while (j < x)
		{
			if (check_player_exist(cont_p[i * x + j], cub) == TRUE)
			{
				*player_y = i;
				*player_x = j;
			}
			j++;
		}
		i++;
	}
	if (cub->conf.pl_counter == 1)
		return (TRUE);
	free_str_safe(cont_p);
	return (FALSE);
}

void
	put_grid_to_container(t_cub *cub, char *cont_p)
{
	int i;
	int j;

	i = 0;
	while (i < cub->conf.map_y + 2)
	{
		j = 0;
		while (j < cub->conf.map_x + 2)
		{
			if (i == 0 || i == cub->conf.map_y + 1 || j == 0 \
					|| j == cub->conf.map_x + 1)
				cont_p[i * (cub->conf.map_x + 2) + j] = 'X';
			else if (i > cub->conf.map_y || j > cub->conf.map_x \
					|| (cub->conf.map)[i - 1][j - 1] == ' ')
				cont_p[i * (cub->conf.map_x + 2) + j] = 's';
			else
				cont_p[i * (cub->conf.map_x + 2) + j] = \
					(cub->conf.map)[i - 1][j - 1];
			j++;
		}
		i++;
	}
}

int
	check_map(t_cub *cub)
{
	int		player_x;
	int		player_y;
	char	*cont_p;

	cont_p = malloc(sizeof(char) \
		* (cub->conf.map_y + 2) * (cub->conf.map_x + 2));
	put_grid_to_container(cub, cont_p);
	if (!pick_player_pl(cont_p, &player_y, &player_x, cub))
	{
		free_cub_map(cub);
		return (error_mes("Error\n No player or more than 2 players\n" \
			, FALSE));
	}
	check_fill(cont_p, player_y, player_x, cub);
	if (cub->conf.map_check_flag == 1)
	{
		free_cub_map(cub);
		free_str_safe(cont_p);
		return (error_mes("Error\n Map is not sorrounded by wall.\n", FALSE));
	}
	cub->conf.pl_y = player_y - 1;
	cub->conf.pl_x = player_x - 1;
	free_str_safe(cont_p);
	return (TRUE);
}
