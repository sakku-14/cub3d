/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:17:46 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/15 19:45:17 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	copy_sprite_first_half(t_cub *cub, int mid, int i)
{
	while (i <= mid)
	{
		cub->tmp[i] = cub->sprite[i];
		i++;
	}
}

void
	copy_sprite_second_half(t_cub *cub, int right, int i, int j)
{
	while (i <= right)
	{
		cub->tmp[i] = cub->sprite[j];
		i++;
		j--;
	}
}

void
	sort_by_dist(t_cub *cub, int left, int right)
{
	int i;
	int j;
	int k;

	i = left;
	j = right;
	k = left;
	while (k <= right)
	{
		if (cub->tmp[i].distance >= cub->tmp[j].distance)
		{
			cub->sprite[k] = cub->tmp[i];
			i++;
		}
		else
		{
			cub->sprite[k] = cub->tmp[j];
			j--;
		}
		k++;
	}
}

void
	mergesort_sprite_structure(t_cub *cub, int left, int right)
{
	int mid;

	if (left >= right)
		return ;
	mid = (left + right) / 2;
	mergesort_sprite_structure(cub, left, mid);
	mergesort_sprite_structure(cub, mid + 1, right);
	copy_sprite_first_half(cub, mid, left);
	copy_sprite_second_half(cub, right, mid + 1, right);
	sort_by_dist(cub, left, right);
}

void
	sort_sprite_structure(t_cub *cub)
{
	ft_bzero(cub->tmp, sizeof(t_sprites) * (cub->sprite_num + 1));
	mergesort_sprite_structure(cub, 0, cub->sprite_num - 1);
}
