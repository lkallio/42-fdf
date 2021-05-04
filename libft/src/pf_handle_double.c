/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:42 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 16:06:18 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_double.h"

static int	handle_mts_malloc(t_dbl *dbl, int i)
{
	dbl->mantissa = (char *)malloc(i + 2);
	if (!dbl->mantissa)
		return (-1);
	dbl->mantissa[i + 1] = 0;
	dbl->dt.mts_len = i;
	return ((int)(dbl->in[1] * 10) > 4);
}

static int	handle_mantissa(t_pf *pf, t_dbl *dbl, int i)
{
	int		out;
	int		ret;

	if (pf->dt.prec > 0)
	{
		dbl->in[1] *= dbl->dt.base;
		out = (int)dbl->in[1];
		dbl->in[1] -= (int)dbl->in[1];
		if (dbl->dt.neg_exp <= i || pf->dt.type < 15
			|| (dbl->dt.opt & 2))
			pf->dt.prec--;
		ret = handle_mantissa(pf, dbl, i + 1);
	}
	else
		return (handle_mts_malloc(dbl, i));
	if (ret == -1)
		return (-1);
	out += ret > 0;
	if ((i == dbl->dt.mts_len - 1) && (dbl->dt.opt & 4)
		&& !(out % dbl->dt.base) && dbl->dt.mts_len--)
		dbl->mantissa[i + 1] = 0;
	else
		dbl->mantissa[i + 1] = dbl_hex_char(pf, dbl, out % dbl->dt.base);
	return (out / dbl->dt.base);
}

static int	handle_whole(t_pf *pf, t_dbl *dbl, intmax_t in, int i)
{
	dbl->dt.whl_len++;
	if (i)
	{
		if (handle_whole(pf, dbl, in / dbl->dt.base, i - 1) == -1)
			return (-1);
	}
	else
	{
		dbl->whole = (char *)malloc(dbl->dt.whl_len + 1);
		if (!dbl->whole)
			return (-1);
		dbl->whole[dbl->dt.whl_len] = 0;
	}
	dbl->whole[i] = dbl_hex_char(pf, dbl, in % dbl->dt.base);
	return (1);
}

static int	dbl_make_printables(t_pf *pf, t_dbl *dbl)
{
	int	ret;

	ret = handle_mantissa(pf, dbl, 0);
	if (ret == -1)
		return (0);
	if (ret > 0)
		dbl->dt.pos_exp += (++dbl->in[0]
				&& !((intmax_t)dbl->in[0] % dbl->dt.base));
	if ((dbl->dt.opt & 2) && (int)dbl->in[0] / dbl->dt.base)
	{
		dbl->dt.opt |= (1 << 3);
		dbl->mantissa[0] = '0';
		dbl->dt.mts_len++;
		dbl->in[0] /= dbl->dt.base;
	}
	if (handle_whole(pf, dbl, (intmax_t)dbl->in[0],
			!!(dbl->dt.opt & 2) * dbl->dt.pos_exp) == -1)
	{
		free(dbl->mantissa);
		return (0);
	}
	return (1);
}

int	handle_double(t_pf *pf, va_list ap)
{
	t_dbl	dbl;

	dbl = (t_dbl){.in = {0}, .dt = {0}, .whole = 0, .mantissa = 0};
	if (pf->dt.length == 'L')
		dbl.in[1] = va_arg(ap, long double);
	else
		dbl.in[1] = (long double)va_arg(ap, double);
	dbl_get_data(pf, &dbl);
	dbl.in[0] = (intmax_t)dbl.in[1];
	dbl.in[1] -= (intmax_t)dbl.in[1];
	if (!dbl_make_printables(pf, &dbl))
		return (-1);
	write_dbl(pf, &dbl);
	return (1);
}
