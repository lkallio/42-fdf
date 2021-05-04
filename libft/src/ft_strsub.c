/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 00:54:16 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 14:18:56 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	ret = (char *)malloc(len + 1);
	if (!ret)
		return (0);
	ret[len] = 0;
	ft_strncpy(ret, s + start, len);
	return (ret);
}
