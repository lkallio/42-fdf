/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:07 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/15 15:27:19 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_pix(int x, int y, float z, t_color color)
{
	static float	*zvals;
	static int		*buf;
	static int		pos[3];
	int				int_color;

	if (!zvals)
	{
		zvals = (float *)get_img()->zvals;
		buf = (int *)get_img()->buf;
		pos[0] = 16 - get_img()->end * 8;
		pos[1] = 8 + get_img()->end * 8;
		pos[2] = get_img()->end * 24;
	}
	if (z > zvals[y * IMG_W + x])
		return ;
	int_color = ((int)(color.r * 0xff) << pos[0])
		| ((int)(color.g * 0xff) << pos[1])
		| ((int)(color.b * 0xff) << pos[2]);
	buf[y * IMG_W + x] = ((int)(color.r * 0xff) << pos[0])
		| ((int)(color.g * 0xff) << pos[1])
		| ((int)(color.b * 0xff) << pos[2]);
	zvals[y * IMG_W + x] = z;
}

static t_vtx	init_set_line(t_vtx start, t_vtx end)
{
	t_vtx	delta;
	float	divisor;

	delta = (t_vtx){
	{end.v[0] - start.v[0], end.v[1] - start.v[1], end.v[2] - start.v[2]},
	{end.color.r - start.color.r,
		end.color.g - start.color.g,
		end.color.b - start.color.b}};
	delta.v[3] = (fabs(delta.v[1]) > fabs(delta.v[0]));
	divisor = 1.0f / fabs(delta.v[(int)delta.v[3]]);
	return ((t_vtx){{delta.v[0] * divisor, delta.v[1] * divisor,
			delta.v[2] * divisor, delta.v[3]},
		{delta.color.r * divisor, delta.color.g * divisor,
			delta.color.b * divisor}});
}

void	set_line(t_vtx start, t_vtx end)
{
	t_vtx	delta;
	int		step;

	delta = init_set_line(start, end);
	step = (int)delta.v[3];
	while ((int)start.v[step] != (int)end.v[step])
	{
		if ((int)start.v[0] >= 0 && (int)start.v[0] < IMG_W
			&& (int)start.v[1] >= 0 && (int)start.v[1] < IMG_H)
			set_pix((int)start.v[0], (int)start.v[1], start.v[2], start.color);
		start.v[0] += delta.v[0];
		start.v[1] += delta.v[1];
		start.v[2] += delta.v[2];
		start.color.r += delta.color.r;
		start.color.g += delta.color.g;
		start.color.b += delta.color.b;
	}
}

void	feed_vtcs(t_vtx start, t_vtx end)
{
	if (start.v[2] < -1.0f || start.v[2] > 1.0f
		|| end.v[2] < -1.0f || end.v[2] > 1.0f)
		return ;
	start.v[0] = (float)((int)((float)IMG_W
				* 0.5f * (start.v[0] + 1.0f) + 0.5f));
	end.v[0] = (float)((int)((float)IMG_W * 0.5f
				* (end.v[0] + 1.0f) + 0.5f));
	start.v[1] = (float)((int)((float)IMG_H * 0.5f
				* (start.v[1] + 1.0f) + 0.5f));
	end.v[1] = (float)((int)((float)IMG_H * 0.5f
				* (end.v[1] + 1.0f) + 0.5f));
	start.v[2] = start.v[2] - 1.0f;
	end.v[2] = end.v[2] - 1.0f;
	set_line(start, end);
}

void	vtclst_to_img(t_vtxl *cur)
{
	while (cur)
	{
		if (cur->rnext)
			feed_vtcs(cur->t, cur->rnext->t);
		if (cur->cnext)
			feed_vtcs(cur->t, cur->cnext->t);
		cur = cur->next;
	}
}
