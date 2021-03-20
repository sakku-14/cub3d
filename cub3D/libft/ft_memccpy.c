/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:03:20 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/20 17:47:27 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned	char	*dst_c;
	unsigned	char	*src_c;

	dst_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	while (n--)
	{
		if (*src_c == (unsigned char)c)
		{
			*dst_c = *src_c;
			return (++dst_c);
		}
		*dst_c++ = *src_c++;
	}
	return (NULL);
}
