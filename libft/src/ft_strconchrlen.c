/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconchrlen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:30:39 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 13:31:10 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strconchrlen(const char *s, int (*f)(int), int truth_value)
{
	if (f(*s) != truth_value || !*s)
		return (0);
	return (1 + ft_strconchrlen(s + 1, f, truth_value));
}
