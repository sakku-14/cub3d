/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:00:27 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/10 11:00:43 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	over_check(long r, char c)
{
	if (r > LONG_MAX / 10 || (r == LONG_MAX / 10 && c - '0' > LONG_MAX % 10))
		return (-1);
	if (r < LONG_MIN / 10 || \
		(r == LONG_MIN / 10 && c - '0' > LONG_MIN % 10 * -1))
		return (0);
	return (1);
}

int			ft_atoi(const char *nptr)
{
	long	result;
	int		p_or_m;

	result = 0;
	p_or_m = 1;
	while (((*nptr >= '\t') && (*nptr <= '\r')) || (*nptr == ' '))
		nptr++;
	if (*nptr == '-')
	{
		p_or_m = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (over_check(result, *nptr) == 1 && ((*nptr >= '0') && (*nptr <= '9')))
	{
		result *= 10;
		if (p_or_m == 1)
			result += *nptr++ - '0';
		else
			result -= *nptr++ - '0';
	}
	if (over_check(result, *nptr) != 1 && ((*nptr >= '0') && (*nptr <= '9')))
		return (over_check(result, *nptr));
	return ((int)result);
}
