/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_dbl_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:17:10 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 14:48:05 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_double.h"

static void	dbl_get_boolean(t_pf *pf, t_dbl *dbl)
{
	if (pf->dt.type > 14 && (pf->dt.type > 16 || dbl->dt.neg_exp > 4
			|| dbl->dt.pos_exp >= pf->dt.prec))
		dbl->dt.opt |= 1 << 1;
	if ((pf->dt.type == 15 || pf->dt.type == 16 || pf->dt.type == 19
			|| pf->dt.type == 20) && !((pf->dt.param & 020)))
		dbl->dt.opt |= 1 << 2;
	if (pf->dt.type > 18)
		dbl->dt.opt |= 1 << 4;
}

void	dbl_get_data(t_pf *pf, t_dbl *dbl)
{
	long double	dbl_test;

	dbl->dt.base = ft_itrn(pf->dt.type > 18, 16, 10);
	pf->dt.prec = ft_itrn(pf->dt.prec < 0, 6, pf->dt.prec);
	if (!pf->dt.prec && pf->dt.type > 14 && pf->dt.type < 17)
		pf->dt.prec = 1;
	if (dbl->in[1] < 0)
	{
		dbl->dt.opt |= 1;
		dbl->in[1] *= -1;
	}
	dbl_test = (intmax_t)dbl->in[1];
	while ((intmax_t)dbl_test / dbl->dt.base && ++dbl->dt.pos_exp)
		dbl_test /= dbl->dt.base;
	dbl_test = 1;
	while (dbl->in[1] && dbl_test > dbl->in[1] && ++dbl->dt.neg_exp)
		dbl_test /= dbl->dt.base;
	dbl_get_boolean(pf, dbl);
	while ((dbl->dt.opt & 2) && (intmax_t)dbl->in[1] / dbl->dt.base)
		dbl->in[1] /= dbl->dt.base;
	while (dbl->in[1] && (dbl->dt.opt & 2) && !(int)dbl->in[1])
		dbl->in[1] *= dbl->dt.base;
	if (pf->dt.type > 14 && pf->dt.type < 17)
		pf->dt.prec -= ft_itrn(!dbl->dt.neg_exp && !(dbl->dt.opt & 2),
				dbl->dt.pos_exp + 1, 1);
}
