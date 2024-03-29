/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:53:18 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/20 17:48:35 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

void
	exit_game(t_cub *cub, int ret)
{
	free_cub(cub, ERROR);
	exit(ret);
}
