/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:05 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/18 14:07:43 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vtxl	*lookaheadr(t_vtxl *start)
{
	float	diff;
	t_vtxl	*n;

	n = start->next;
	if (!n || n->v.v[2] != start->v.v[2])
		return (0);
	diff = ((n->v.v[0] - start->v.v[0])
			/ (n->v.v[1] - start->v.v[1]));
	while (n->next && n->next->v.v[2] == n->v.v[2])
	{
		if (!(get_args()->flags & FDF_OPT)
			|| ((n->next->v.v[0] - n->v.v[0])
				/ (n->next->v.v[1] - n->v.v[1])) != diff)
			break ;
		n->unused |= 0b01;
		n = n->next;
	}
	return (n);
}

t_vtxl	*lookaheadc(t_vtxl *start)
{
	float	diff;
	int		diff_set;
	t_vtxl	*n;
	t_vtxl	*ret;

	n = start;
	ret = 0;
	diff_set = 0;
	while (n && n->next && (!diff_set
			|| (get_args()->flags & FDF_OPT)))
	{
		n = n->next;
		if (n->v.v[0] != start->v.v[0])
			continue ;
		if (!diff_set && ft_intass(&diff_set, 1))
			diff = ((n->v.v[1] - start->v.v[1])
					/ (n->v.v[2] - start->v.v[2]));
		else if (((n->v.v[1] - ret->v.v[1])
				/ (n->v.v[2] - ret->v.v[2])) != diff)
			break ;
		if (ret)
			ret->unused |= 0b10;
		ret = n;
	}
	return (ret);
}

void	connect_nodes(t_vtxl *cur)
{
	while (cur)
	{
		if (!(cur->unused & 0b01))
			cur->rnext = lookaheadr(cur);
		if (!(cur->unused & 0b10))
			cur->cnext = lookaheadc(cur);
		cur = cur->next;
	}
}

void	remove_unused_vtcs(register t_vtxl *cur)
{
	register t_vtxl		*temp;
	register int		*count;

	count = (int [2]){0};
	while (cur && cur->next)
	{
		count[1]++;
		if (cur->next->unused == 0b11)
		{
			temp = cur->next;
			cur->next = temp->next;
			free(temp);
			count[0]++;
			continue ;
		}
		cur = cur->next;
	}
	if (get_args()->flags & FDF_VERB)
		ft_printf("Removed %d/%d vertices,totalling %lu bytes.\n",
			count[0], count[1], count[0] * sizeof(t_vtxl));
}

void	data_setup(t_vtxl *vtcs)
{
	t_dim	*d;

	connect_nodes(vtcs);
	if (get_args()->flags & FDF_OPT)
		remove_unused_vtcs(vtcs);
	d = init_dim();
	if (get_args()->flags & FDF_GRAD)
		sig_color(vtcs);
	mul_all(vtcs, m_trans(d->xmax / 2.0f,
			-(d->ymax - d->ymin) / 2.0f, -d->zmax / 2.0f), 1);
	mul_all(vtcs, m_scale(1.0f / d->allmax,
			1.0f / d->yabsmax, 1.0f / d->allmax), 1);
	if (get_args()->flags & FDF_NOISO)
		return ;
	*m_world() = m_mul(*m_world(), m_xrot(0.6155f));
	*m_world() = m_mul(*m_world(), m_yrot(-M_PI / 4.0f));
}
