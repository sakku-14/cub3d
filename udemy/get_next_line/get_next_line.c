/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 13:39:50 by ysakuma           #+#    #+#             */
/*   Updated: 2020/11/18 10:42:44 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_erroract(char **save, char **line, char *buf)
{
	free(*save);
	*save = NULL;
	free(buf);
	buf = NULL;
	if (line)
	{
		free(*line);
		*line = NULL;
	}
	return (-1);
}

static int	gnl_overwite(char **save, char **line, char *buf)
{
	size_t	len;
	size_t	len_after;
	char	*tmp;

	len = 0;
	while (*(*save + len) != '\n')
		len++;
	if (!(*line = malloc(sizeof(char) * (len + 1))))
		return (gnl_erroract(save, NULL, buf));
	ft_strlcpy(*line, *save, len + 1);
	len_after = ft_strlen(*save + len + 1);
	if (!(tmp = malloc(sizeof(char) * (len_after + 1))))
		return (gnl_erroract(save, line, buf));
	ft_strlcpy(tmp, *save + len + 1, len_after + 1);
	free(*save);
	*save = tmp;
	free(buf);
	buf = NULL;
	return (1);
}

static int	gnl_attach(char *buf, char **save, ssize_t len)
{
	size_t	ori_len;
	char	*tmp;

	ori_len = ft_strlen(*save);
	if (!(tmp = malloc(sizeof(char) * (ori_len + len + 1))))
		return (1);
	ft_strlcpy(tmp, *save, ori_len + 1);
	ft_strlcat(tmp, buf, ori_len + len + 1);
	free(*save);
	*save = tmp;
	return (0);
}

static int	gnl_lastact(char **save, char **line, char *buf)
{
	size_t	len;

	len = ft_strlen(*save);
	if (!(*line = malloc(sizeof(char) * (len + 1))))
		return (gnl_erroract(save, NULL, buf));
	ft_strlcpy(*line, *save, len + 1);
	free(buf);
	buf = NULL;
	free(*save);
	*save = NULL;
	return (0);
}

int			get_next_line(int fd, char **line)
{
	ssize_t		len;
	static char	*save[MAX_FD];
	char		*buf;

	if (!line || fd < 0 || fd > MAX_FD)
		return (-1);
	if (!save[fd])
		if (!(save[fd] = ft_calloc(1, sizeof(char))))
			return (-1);
	if (!(buf = malloc(BUFFER_SIZE)))
		return (gnl_erroract(&save[fd], NULL, NULL));
	if (ft_memchr(save[fd], '\n', ft_strlen(save[fd])))
		return (gnl_overwite(&save[fd], line, buf));
	while ((len = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		if (gnl_attach(buf, &save[fd], len))
			return (gnl_erroract(&save[fd], NULL, buf));
		if (ft_memchr(buf, '\n', len))
			return (gnl_overwite(&save[fd], line, buf));
		if (len < BUFFER_SIZE)
			return (gnl_lastact(&save[fd], line, buf));
	}
	return (gnl_erroract(&save[fd], NULL, buf));
}
