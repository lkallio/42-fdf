/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:13 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/15 15:02:18 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_readvtcs	*get_last(void)
{
	static t_readvtcs	v[1];

	return (v);
}

t_mlx	*get_mw(void)
{
	static t_mlx	mw[1];

	if (!mw->m)
	{
		mw->m = mlx_init();
		mw->w = mlx_new_window(mw->m, WIN_W, WIN_H, "fdf");
	}
	return (mw);
}

t_img	*get_img(void)
{
	static t_img	i[1];

	if (!i->ip)
	{
		i->ip = mlx_new_image(get_mw()->m,
				IMG_W + (IMG_W % 2), IMG_H + (IMG_H % 2));
		i->buf = mlx_get_data_addr(i->ip, &i->bpp, &i->sl, &i->end);
		i->zvals = malloc(IMG_W * IMG_H * sizeof(float));
		if (!i->buf || !i->zvals)
			fdf_usage();
		i->buf_size = (i->sl
				* (IMG_H + (IMG_H % 2))) / sizeof(long long);
		i->zvals_size = ((IMG_W + (IMG_W % 2))
				* (IMG_H + (IMG_H % 2)) * sizeof(float))
			/ sizeof(long long);
	}
	return (i);
}

t_dim	*get_dim(void)
{
	static t_dim	dim[1] = {{.xmax = 1.0f, .zmax = 1.0f}};

	return (dim);
}

t_args	*get_args(void)
{
	static t_args	args[1];
	static int		set;

	if (!set && ++set)
		args[0] = (t_args){.flags = FDF_DEFAULTOPT | FDF_NOSTRDEFAULT,
			.color = 0xffffff};
	return (args);
}
