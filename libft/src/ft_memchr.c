/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 00:53:06 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 12:42:06 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*area;

	area = (unsigned char *)s;
	while (n--)
	{
		if (*area == (unsigned char)c)
			return (area);
		if (*area)
			area++;
	}
	return (0);
}
