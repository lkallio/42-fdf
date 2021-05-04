/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:52:34 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 14:13:38 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strpush(char ***strarr_ptr, char *newstr, size_t i)
{
	char	*str_ins;

	if (*strarr_ptr && (*strarr_ptr)[i])
	{
		str_ins = (*strarr_ptr)[i];
		ft_strpush(strarr_ptr, newstr, i + 1);
	}
	else if (newstr)
	{
		if (*strarr_ptr)
			free(*strarr_ptr);
		*strarr_ptr = (char **)malloc(sizeof(char *) * (i + 2));
		if (*strarr_ptr)
			(*strarr_ptr)[i + 1] = 0;
		str_ins = newstr;
	}
	if (*strarr_ptr && newstr)
		(*strarr_ptr)[i] = str_ins;
	return ((!*strarr_ptr || !newstr) * -1);
}
