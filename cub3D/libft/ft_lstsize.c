/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:02:37 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/20 17:47:25 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int counter;

	counter = 0;
	if (!lst)
		return (0);
	while (lst->next)
	{
		counter++;
		lst = lst->next;
	}
	return (++counter);
}
