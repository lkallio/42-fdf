/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:01 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/15 15:27:25 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_color	get_color(char *inp, int i)
{
	register int	color;

	while (inp[i] && inp[i] != ',' && inp[i] != ' ' && inp[i] != '\n')
		i++;
	if (inp[i] == ',' && !(get_args()->flags & FDF_COLOR))
	{
		if (get_args()->flags & (FDF_DEFAULTOPT | FDF_DEFAULTGRAD))
			get_args()->flags &= ~(FDF_DEFAULTOPT | FDF_DEFAULTGRAD);
		color = ft_strtol(inp + i + 1, 0, 0);
		return ((t_color){.r = ((color >> 16) & 0xff) / (float)0xff,
			.g = ((color >> 8) & 0xff) / (float)0xff,
			.b = (color & 0xff) / (float)0xff});
	}
	else
		color = get_args()->color;
	return ((t_color){.r = ((color >> 16) & 0xff) / (float)0xff,
		.g = ((color >> 8) & 0xff) / (float)0xff,
		.b = (color & 0xff) / (float)0xff});
}

void	sig_color(t_vtxl *cur)
{
	register float		y;
	register float		sig_y;
	static float		sig_width;
	static int			set;

	if (!set && ++set)
		sig_width = fabs(get_dim()->ymax - get_dim()->ymin) * 0.5f;
	while (cur)
	{
		y = (cur->v.v[1] - (sig_width));
		sig_y = 0.5f * (y / (sig_width + fabs(y))) + 0.5f;
		cur->v.color.r = fabs(cur->v.color.r - sig_y);
		cur->v.color.g = fabs(cur->v.color.g - sig_y);
		cur->v.color.b = fabs(cur->v.color.b - sig_y);
		cur = cur->next;
	}
}

t_dim	*init_dim(void)
{
	t_dim	*d;

	d = get_dim();
	if (d->ymax > fabs(d->ymin))
		d->yabsmax = d->ymax;
	else
		d->yabsmax = fabs(d->ymin);
	if (!d->yabsmax)
		d->yabsmax = 1.0f;
	if (d->xmax > d->zmax)
		d->allmax = d->xmax / 2.0f;
	else
		d->allmax = d->zmax / 2.0f;
	if (d->allmax > d->yabsmax)
		d->yabsmax = d->allmax;
	return (d);
}
