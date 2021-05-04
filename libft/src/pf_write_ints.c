/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write_ints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:55 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 16:50:44 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_char(int num, t_pf *pf, int base)
{
	if (pf->dt.type == 4)
		return (num);
	if (base == 16 && num >= 10)
		return (num - 10 + ft_itrn(pf->dt.type == 7, 'a', 'A'));
	else
		return ('0' + num);
}

static void	prepend(t_pf *pf)
{
	if (pf->dt.type == 6 && (pf->dt.param & 020))
		handle_buffer(pf, '0');
	else if ((pf->dt.type >= 7 && pf->dt.type <= 10)
		&& (pf->dt.param & 020))
	{
		handle_buffer(pf, '0');
		if (pf->dt.type == 7 || pf->dt.type == 8)
			handle_buffer(pf, ft_itrn(pf->dt.type == 7, 'x', 'X'));
		else
			handle_buffer(pf, ft_itrn(pf->dt.type == 9, 'b', 'B'));
	}
	else if (pf->dt.param & (1 << 5) && pf->dt.type >= 2 && pf->dt.type <= 4)
		handle_buffer(pf, '-');
	else if ((pf->dt.param & 2) && pf->dt.type >= 2 && pf->dt.type <= 4)
		handle_buffer(pf, '+');
	else if ((pf->dt.param & 4) && pf->dt.type >= 2 && pf->dt.type <= 4)
		handle_buffer(pf, ' ');
}

int	write_int(uintmax_t in, t_pf *pf, int base, int i)
{
	if ((in || (!i && pf->dt.prec)) && write_int(in / base, pf, base, i + 1))
		handle_buffer(pf, hex_char(in % base, pf, base));
	else if (i < pf->dt.prec && write_int(in, pf, base, i + 1))
		handle_buffer(pf, '0');
	else if (pf->dt.prec == -1 && (pf->dt.param & 010) && i < pf->dt.width
		&& !((pf->dt.param & 1))
		&& write_int(in, pf, base, i + 1))
		handle_buffer(pf, '0');
	else if (!pf->dt.temp++ && write_int(in, pf, base, i))
		prepend(pf);
	else if (!((pf->dt.param & 1)) && i < pf->dt.width && write_int(in, pf,
			base, i + 1))
		handle_buffer(pf, ' ');
	else
		pf->dt.num_len = i;
	return (1);
}
