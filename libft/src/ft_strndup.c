/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:19:02 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 16:55:25 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*copy;

	copy = (char *)malloc(n + 1);
	if (!copy)
		return (0);
	ft_strncpy(copy, s, n);
	copy[n] = 0;
	return (copy);
}
