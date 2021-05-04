/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:25 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/15 15:45:09 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vtxl	*vtxl_node(t_vtxl *ret, t_vtx pos)
{
	t_vtxl	*cur;

	cur = (t_vtxl *)malloc(sizeof(t_vtxl));
	if (!cur)
		fdf_usage();
	cur->next = ret;
	if (!cur->next)
	{
		get_last()->cur = cur;
		get_last()->pos = pos;
	}
	cur->v = pos;
	cur->unused = 0;
	cur->rnext = 0;
	cur->cnext = 0;
	return (cur);
}

t_vtxl	*read_vtcs(char *inp, t_vtx pos, int i, int *r)
{
	pos.v[0] -= (float)(inp[i] == ' ');
	while (inp[i] == ' ' || inp[i] == '\n')
	{
		if (inp[i++] == '\n')
		{
			if (fabs(pos.v[0]) > get_dim()->xmax)
				get_dim()->xmax = fabs(pos.v[0]);
			get_dim()->zmax = ++pos.v[2];
			pos.v[0] = 0.0f;
		}
	}
	if (!inp[i] || (++(*r) > 2048 && ft_intass(&get_last()->i, i)))
		return (0);
	pos.v[1] = atoi(inp + i);
	if (pos.v[1] > get_dim()->ymax)
		get_dim()->ymax = pos.v[1];
	if (!get_dim()->ymin || pos.v[1] < get_dim()->ymin)
		get_dim()->ymin = pos.v[1];
	pos.color = get_color(inp, i);
	while (inp[i] && inp[i] != ' ' && inp[i] != '\n')
		i++;
	return (vtxl_node(
			read_vtcs(inp, pos, i, r),
			pos));
}

t_vtxl	*read_vtcs_chunks(char *inp)
{
	int		r;
	t_vtxl	*vtcs;
	t_vtxl	*last;

	if (!inp)
		fdf_usage();
	r = 0;
	vtcs = read_vtcs(inp, (t_vtx){{[3] = 1.0f}, {0}}, 0, &r);
	while (r > 2048)
	{
		last = get_last()->cur;
		r = 0;
		last->next = read_vtcs(inp, get_last()->pos,
				get_last()->i, &r);
	}
	return (vtcs);
}
