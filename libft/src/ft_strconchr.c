/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:28:33 by lkallio           #+#    #+#             */
/*   Updated: 2019/10/31 19:50:18 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strconchr(const char *s, int (*f)(int), int truth_value)
{
	if (f(*s) != truth_value)
		return ((char *)s);
	if (!*s)
		return (0);
	return (ft_strconchr(++s, f, truth_value));
}
