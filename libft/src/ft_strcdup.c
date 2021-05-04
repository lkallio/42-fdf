/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:49:43 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 13:21:32 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcdup(char **dst, const char *src, int c, int i)
{
	if (*src != c && *src)
		return (ft_strcdup(dst, src + 1, c, i + 1) && ((*dst)[i] = *src));
	else
	{
		*dst = (char *)malloc(i + 1);
		if (!*dst)
			return (-1);
		(*dst)[i] = 0;
		return (*src == c);
	}
}
