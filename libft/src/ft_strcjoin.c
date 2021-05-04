/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:56:09 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 13:30:34 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcjoin(char **dst, char *src, char stop, int count)
{
	char	c;
	int		ret;

	if (**dst)
	{
		c = **dst;
		(*dst)++;
		ret = ft_strcjoin(dst, src, stop, count + 1);
	}
	else if (*src && *src != stop)
	{
		c = *src;
		ret = ft_strcjoin(dst, src + 1, stop, count + 1);
	}
	else
	{
		*dst = (char *)malloc(count + 1);
		if (!*dst)
			return (-1);
		dst[0][count] = 0;
		return (*src == stop);
	}
	if (ret != -1)
		dst[0][count] = c;
	return (ret);
}
