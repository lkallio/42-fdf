/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:53 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 16:46:13 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_double.h"

static void	write_sci_suffix(t_pf *pf, t_dbl *dbl)
{
	int		dbl_exponent;

	dbl_exponent = ft_itrn(!!dbl->dt.neg_exp, dbl->dt.neg_exp, dbl->dt.pos_exp);
	if (pf->dt.type == 15 || pf->dt.type == 17)
		handle_buffer(pf, 'e');
	else if (pf->dt.type == 16 || pf->dt.type == 18)
		handle_buffer(pf, 'E');
	if (pf->dt.type > 18)
		handle_buffer(pf, ft_itrn(pf->dt.type == 19, 'p', 'P'));
	if (dbl->dt.neg_exp > 0)
		handle_buffer(pf, '-');
	else
		handle_buffer(pf, '+');
	handle_buffer(pf, (dbl_exponent / 10) % 10 + '0');
	handle_buffer(pf, dbl_exponent % 10 + '0');
}

static void	write_dbl_num(t_pf *pf, t_dbl *dbl)
{
	if (pf->dt.type > 18)
		feedbuf_str(pf, ft_stern(pf->dt.type == 19, "0x", "0X"), 2);
	feedbuf_str(pf, dbl->whole, dbl->dt.whl_len);
	if (dbl->dt.mts_len || (pf->dt.param & 020))
		handle_buffer(pf, '.');
	feedbuf_str(pf, dbl->mantissa + !(dbl->dt.opt & 010),
		dbl->dt.mts_len);
	if (dbl->dt.opt & 2)
		write_sci_suffix(pf, dbl);
}

void	write_dbl(t_pf *pf, t_dbl *dbl)
{
	int		total_len;

	total_len = ((dbl->dt.opt & 1) || (pf->dt.param & 4)) + dbl->dt.whl_len
		+ (dbl->dt.mts_len || (pf->dt.param & 020)) + dbl->dt.mts_len
		+ !!(dbl->dt.opt & 2) * 4 + (pf->dt.type > 18) * 2;
	if ((dbl->dt.opt & 1) && (pf->dt.param & 010))
		handle_buffer(pf, '-');
	if (((pf->dt.param & 2) || (pf->dt.param & 4))
		&& (pf->dt.param & 010) && !(dbl->dt.opt & 1))
		handle_buffer(pf, ft_itrn((pf->dt.param & 2), '+', ' '));
	if (!((pf->dt.param & 1)))
		feedbuf_nchar(pf, ft_itrn((pf->dt.param & 010), '0', ' '),
			pf->dt.width - total_len);
	if ((dbl->dt.opt & 1) && !((pf->dt.param & 010)))
		handle_buffer(pf, '-');
	if (((pf->dt.param & 2) || (pf->dt.param & 4))
		&& !((pf->dt.param & 010)) && !(dbl->dt.opt & 1))
		handle_buffer(pf, ft_itrn((pf->dt.param & 2), '+', ' '));
	write_dbl_num(pf, dbl);
	if (pf->dt.param & 1)
		feedbuf_nchar(pf, ' ', pf->dt.width - total_len);
	free(dbl->whole);
	free(dbl->mantissa);
}

int	dbl_hex_char(t_pf *pf, t_dbl *dbl, int num)
{
	if ((dbl->dt.opt & 020) && num > 10)
		return (num - 10 + ft_itrn(pf->dt.type == 19, 'a', 'A'));
	else
		return ('0' + num);
}
