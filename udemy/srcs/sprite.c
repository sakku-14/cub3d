/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:18:19 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 12:39:28 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	set_last_sprite(t_cub *cub, int k)
{
	cub->sprite[k].sprite_x = -1;
	cub->sprite[k].sprite_y = -1;
	cub->sprite[k].visible = -1;
}

void
	count_sprite_num(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	cub->sprite_num = 0;
	while (i < cub->conf.map_y)
	{
		j = 0;
		while (j < cub->conf.map_x)
		{
			if ((cub->conf.map)[i][j] == '2')
				cub->sprite_num++;
			j++;
		}
		i++;
	}
}

int
	set_sprites(t_cub *cub)
{
	int i;
	int j;
	int num;

	i = 0;
	num = 0;
	while (i < cub->conf.map_y)
	{
		j = 0;
		while (j < cub->conf.map_x && num < cub->sprite_num)
		{
			if ((cub->conf.map)[i][j] == '2')
			{
				cub->sprite[num].sprite_y = i;
				cub->sprite[num].sprite_x = j;
				cub->sprite[num].visible = 0;
				num++;
			}
			j++;
		}
		i++;
	}
	return (num);
}

int
	check_sprite_info(t_cub *cub)
{
	int num;

	count_sprite_num(cub);
	if (!(cub->sprite = malloc(sizeof(t_sprites) * (cub->sprite_num + 1))))
		return (FALSE);
	ft_bzero(cub->sprite, sizeof(t_sprites) * (cub->sprite_num + 1));
	if (!(cub->tmp = malloc(sizeof(t_sprites) * (cub->sprite_num + 1))))
	{
		free(cub->sprite);
		cub->sprite = NULL;
		return (FALSE);
	}
	num = set_sprites(cub);
	set_last_sprite(cub, num);
	return (TRUE);
}
