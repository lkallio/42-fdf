/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconchrrlen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:32:57 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 13:31:16 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strconchrrlen(const char *s, int (*f)(int), int truth_value)
{
	int		len;
	int		index;

	len = ft_strlen(s);
	index = len;
	while (index--)
		if (f(s[index]) != truth_value)
			return (index);
	return (len);
}
