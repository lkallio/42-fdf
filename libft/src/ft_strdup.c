/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 12:17:54 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 16:56:05 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *)malloc(ft_strlen(src) + 1);
	if (!copy)
		return (0);
	while (*src)
		copy[i++] = *(src++);
	copy[i] = 0;
	return (copy);
}
