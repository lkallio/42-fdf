/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:54:39 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 12:19:13 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_append(void *addr, size_t new_size, size_t mem_size)
{
	size_t			old_size;
	unsigned char	*old;
	unsigned char	*new;

	if (!new_size)
		return (0);
	old = (unsigned char *)addr;
	old_size = (new_size - 1) * mem_size;
	new = (unsigned char *)malloc(new_size * mem_size);
	if (!new)
		return (0);
	while (old_size--)
		new[old_size] = old[old_size];
	if (addr)
		free(addr);
	return ((void *)new);
}
