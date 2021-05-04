/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 16:18:48 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 14:17:54 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstrjoin(char **dst, char *src, char *stop, int count)
{
	char	c;
	int		ret;

	if (**dst)
	{
		c = **dst;
		(*dst)++;
		ret = ft_strstrjoin(dst, src, stop, count + 1);
	}
	else if (*src && !ft_strchr(stop, *src))
	{
		c = *src;
		ret = ft_strstrjoin(dst, src + 1, stop, count + 1);
	}
	else
	{
		*dst = (char *)malloc(count + 1);
		dst[0][count] = 0;
		return (!!ft_strchr(stop, *src));
	}
	dst[0][count] = c;
	return (ret);
}
