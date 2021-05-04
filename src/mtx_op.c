/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:20 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/17 16:11:29 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mtx	*m_view(void)
{
	static int		set;
	static t_mtx	view;

	if (!set && ++set)
	{
		view = (t_mtx){{{{-1.0f, 0, 0, 0}, {0}},
		{{0, -1.0f, 0, 0}, {0}},
		{{0, 0, -1.0f, 0}, {0}},
		{{0, 0.0f, 2.8f, 1.0f}, {0}}}};
		if (!(get_args()->flags & (FDF_ORTH | FDF_NOISO)))
			view.m[3].v[1] = -0.3f;
	}
	return (&view);
}

t_mtx	*m_world(void)
{
	static int		set;
	static t_mtx	world;

	if (!set && ++set)
	{
		world = m_idty();
		if (get_args()->flags & FDF_ORTH)
			world = m_mul(world, m_scale(0.9f, 0.9f, 0.9f));
	}
	return (&world);
}

t_mtx	*m_proj(void)
{
	static t_mtx	proj;
	static int		set;
	float			ar;

	if (set)
		return (&proj);
	ar = ((float)IMG_W / (float)IMG_H);
	if (!(get_args()->flags & FDF_ORTH))
		proj = (t_mtx){{
		{{[0] = 1.0f / (tan(P_FOV / 2.0f) * ar)}, {0}},
		{{[1] = 1.0f / tan(P_FOV / 2.0f)}, {0}},
		{{0, 0, - (P_NEAR + P_FAR)
			/ (P_NEAR - P_FAR), 1.0f}, {0}},
		{{[2] = 2.0f * P_FAR * P_NEAR
			/ (P_NEAR - P_FAR)}, {0}}
		}};
	else
		proj = (t_mtx){{
		{{[0] = 1.0f / (ar * 1.3f)}, {0}}, {{[1] = 1.0f / 1.3f}, {0}},
		{{[2] = 2.0f / (P_FAR - P_NEAR)}, {0}},
		{{0, 0, - (P_FAR + P_NEAR)
			/ (P_FAR - P_NEAR), 1.0f}, {0}}
		}};
	set = 1;
	return (&proj);
}

void	update(t_mtx *m, float a, int flag)
{
	t_mtx			(*r)(float);

	if (flag & UD_ROT)
	{
		r = m_zrot;
		if (flag & (UD_RX | UD_RY))
			r = ft_ptern(flag & UD_RX, (void *)m_xrot, (void *)m_yrot);
		if (get_args()->flags & FDF_CAMERA)
			*m = m_mul(r(a), *m);
		else
			*m = m_mul(*m, r(a));
	}
	else if (flag & (UD_TX | UD_TY))
		(*m).m[3].v[!!(flag & UD_TY)] += a;
	else if (get_args()->flags & FDF_ORTH)
	{
		a = 1.0f - a;
		*m = m_mul(*m, m_scale(a, a, a));
	}
	else
		(*m).m[3].v[2] += a;
}

t_mtx	model_to_screen(void)
{
	static t_mtx	m;

	m = m_idty();
	m = m_mul(*m_world(), m);
	m = m_mul(*m_view(), m);
	m = m_mul(*m_proj(), m);
	return (m);
}
