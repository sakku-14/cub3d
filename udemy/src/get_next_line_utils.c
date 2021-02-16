/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:43:34 by ysakuma           #+#    #+#             */
/*   Updated: 2020/11/10 17:39:34 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*ret;
	size_t			i;
	unsigned char	*ret_c;

	if (!(ret = malloc(count * size)))
		return (NULL);
	ret_c = (unsigned char *)ret;
	i = 0;
	while (i < count * size)
		ret_c[i++] = 0;
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char		*src_c;
	size_t		len;

	src_c = (char *)src;
	len = ft_strlen(src);
	while (dstsize > 1 && *src_c)
	{
		*dst++ = *src_c++;
		dstsize--;
	}
	if (dstsize)
		*dst = '\0';
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_c;

	s_c = (unsigned char *)s;
	while (n--)
	{
		if (*s_c++ == (unsigned char)c)
			return ((void*)s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t len;
	size_t room;

	if (dstsize < ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	else
		len = ft_strlen(dst) + ft_strlen(src);
	room = dstsize - 1 - ft_strlen(dst);
	while (*dst)
		dst++;
	ft_strlcpy(dst, src, room + 1);
	return (len);
}
