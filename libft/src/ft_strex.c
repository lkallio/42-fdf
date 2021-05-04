/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 13:51:26 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 14:02:56 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*make_ret(int *ept, register int i)
{
	char	*ret;

	if (!ept[1])
		ept[1] = i;
	ret = (char *)malloc(ept[1] - ept[0] + 1);
	if (ret)
		ret[ept[1] - ept[0]] = 0;
	return (ret);
}

static char	*ft_rstrex(const char *s, char *p, register int i)
{
	static int	ept[2];
	char		*ret;

	if (*p == '(' && *++p)
		ept[0] = i;
	if (*p == ')' && *++p)
		ept[1] = i;
	if (*s != *p && *p != '*')
		return (0);
	if (!*s && (!*p || *p == '*'))
		return (make_ret(ept, i));
	ret = ft_rstrex(s + 1, p + !(*p == '*' && p[1] != *s), i + 1);
	if (ret && i >= ept[0] && i <= ept[1])
		ret[i - ept[0]] = *s;
	if (!i)
	{
		ept[0] = 0;
		ept[1] = 0;
	}
	return (ret);
}

char	*ft_strex(const char *s, char *p)
{
	static char	*ret;

	if (!s && !p)
		return (ret);
	if (ret)
		free(ret);
	return ((ret = ft_rstrex(s, p, 0)));
}
