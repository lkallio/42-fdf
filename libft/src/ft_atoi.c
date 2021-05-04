/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:15:45 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 12:20:07 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	atoi_assistant(const char *str, long ret)
{
	if (*str < '0' || *str > '9')
		return (ret);
	return (atoi_assistant(str + 1, (long)ret * 10 + *str - '0'));
}

int	ft_atoi(const char *str)
{
	long	a;

	if (ft_iswspace(*str))
		return (ft_atoi(str + 1));
	else if (*str == '-')
		a = -atoi_assistant(++str, 0);
	else if (*str == '+')
		a = atoi_assistant(++str, 0);
	else
		a = atoi_assistant(str, 0);
	return ((int)a);
}
