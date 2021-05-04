/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stpncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 00:53:27 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 13:20:13 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stpncpy(char *dst, const char *src, size_t len)
{
	int	i;

	i = -(!!len);
	while (len--)
	{
		if (*src)
			dst[++i] = *src++;
		else
			dst[++i] = 0;
	}
	return (dst + i);
}
