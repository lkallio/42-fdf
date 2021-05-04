/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:23 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/15 15:41:07 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mtx	m_trans(float x, float y, float z)
{
	return ((t_mtx){{
			{{1.0f, 0, 0, 0}, {0}},
			{{0, 1.0f, 0, 0}, {0}},
			{{0, 0, 1.0f, 0}, {0}},
			{{x, y, z, 1.0f}, {0}}
		}});
}

t_mtx	m_scale(float x, float y, float z)
{
	return ((t_mtx){{
			{{x, 0, 0, 0}, {0}},
			{{0, y, 0, 0}, {0}},
			{{0, 0, z, 0}, {0}},
			{{0, 0, 0, 1.0f}, {0}}
		}});
}

t_vtx	v_mul(t_vtx vtx, t_mtx mtx)
{
	return ((t_vtx){
		.v = {
			vtx.v[0] * mtx.m[0].v[0]
			+ vtx.v[1] * mtx.m[1].v[0]
			+ vtx.v[2] * mtx.m[2].v[0]
			+ vtx.v[3] * mtx.m[3].v[0],
			vtx.v[0] * mtx.m[0].v[1]
			+ vtx.v[1] * mtx.m[1].v[1]
			+ vtx.v[2] * mtx.m[2].v[1]
			+ vtx.v[3] * mtx.m[3].v[1],
			vtx.v[0] * mtx.m[0].v[2]
			+ vtx.v[1] * mtx.m[1].v[2]
			+ vtx.v[2] * mtx.m[2].v[2]
			+ vtx.v[3] * mtx.m[3].v[2],
			vtx.v[0] * mtx.m[0].v[3]
			+ vtx.v[1] * mtx.m[1].v[3]
			+ vtx.v[2] * mtx.m[2].v[3]
			+ vtx.v[3] * mtx.m[3].v[3]
		},
		.color = vtx.color
	});
}

t_mtx	m_mul(t_mtx d, t_mtx s)
{
	return ((t_mtx){
		v_mul(s.m[0], d),
		v_mul(s.m[1], d),
		v_mul(s.m[2], d),
		v_mul(s.m[3], d)
	});
}

void	mul_all(t_vtxl *cur, t_mtx m, int apply)
{
	float	divisor;

	while (cur)
	{
		cur->t = v_mul(cur->v, m);
		divisor = 1.0f / cur->t.v[3];
		cur->t.v[0] *= divisor;
		cur->t.v[1] *= divisor;
		cur->t.v[2] *= divisor;
		cur->t.v[3] *= divisor;
		if (apply)
			cur->v = cur->t;
		cur = cur->next;
	}
}
