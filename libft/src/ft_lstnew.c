/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 02:53:59 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 12:39:05 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	if (!content && content_size)
		return (ft_lstnew(content, 0));
	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (0);
	if (content_size)
		lst->content = malloc(content_size);
	if (content_size && !lst->content)
	{
		free(lst);
		return (0);
	}
	if (content_size)
		lst->content = ft_memcpy(lst->content, content, content_size);
	lst->content_size = content_size;
	lst->next = 0;
	return (lst);
}
