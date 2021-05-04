/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:43:53 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 12:20:23 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *addr, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)addr;
	while (n--)
		*p++ = 0;
}
