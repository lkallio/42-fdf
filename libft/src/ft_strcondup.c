/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcondup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:14:27 by lkallio           #+#    #+#             */
/*   Updated: 2019/10/31 19:54:52 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcondup(const char *src, int (*f)(int), int truth_value)
{
	return (ft_strndup(src, ft_strconchrlen(src, f, truth_value)));
}
