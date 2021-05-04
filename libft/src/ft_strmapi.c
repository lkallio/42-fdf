/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 02:00:54 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 14:11:22 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_string_assign(char **p, char const *s,
		char (*f)(unsigned int, char), unsigned int i)
{
	if (!*s)
	{
		(*p)[i] = 0;
		return ;
	}
	(*p)[i] = f(i, *s);
	ft_string_assign(p, s + 1, f, i + 1);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;

	p = NULL;
	if (s && f)
		p = (char *)malloc(ft_strlen(s) + 1);
	if (!p)
		return (0);
	ft_string_assign(&p, s, f, 0);
	return (p);
}
