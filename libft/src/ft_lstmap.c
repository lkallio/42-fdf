/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 02:27:32 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 12:37:38 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*l;

	if (lst)
	{
		l = f(lst);
		if (!l)
			return (0);
		if (lst->next)
			l->next = ft_lstmap(lst->next, f);
		if (lst->next && !l->next)
		{
			free(l);
			return (0);
		}
		return (l);
	}
	return (0);
}
