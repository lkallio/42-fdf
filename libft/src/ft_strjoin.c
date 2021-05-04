/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 00:53:45 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 16:52:57 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	char	*ret;

	s1_len = ft_strlen((char *)s1);
	ret = (char *)malloc(s1_len + ft_strlen(s2) + 1);
	if (!ret)
		return (0);
	ft_strcpy(ret, s1);
	ft_strcpy(ret + s1_len, s2);
	return (ret);
}
