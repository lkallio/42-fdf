/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_n_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:48 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 16:16:40 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_str(t_pf *pf, va_list ap)
{
	char		*print;
	int			arg_len;
	static char	null[] = "(null)";

	print = va_arg(ap, char *);
	if (!print)
		print = null;
	arg_len = ft_strlen(print);
	if (arg_len > pf->dt.prec && pf->dt.prec != -1)
		arg_len = pf->dt.prec;
	if (!((pf->dt.param & 1)))
		feedbuf_nchar(pf, ft_itrn((pf->dt.param & 010), '0', ' '),
			pf->dt.width - arg_len);
	feedbuf_str(pf, print, arg_len);
	if ((pf->dt.param & 1))
		feedbuf_nchar(pf, ' ', pf->dt.width - arg_len);
	return (1);
}

int	handle_n(t_pf *pf, va_list ap)
{
	int		*target;

	target = va_arg(ap, int *);
	*target = pf->n + pf->buf_idx;
	return (1);
}

int	handle_c(t_pf *pf, va_list ap)
{
	char	c;

	c = (char)va_arg(ap, int);
	if (!((pf->dt.param & 1)))
		feedbuf_nchar(pf, ft_itrn((pf->dt.param & 010), '0', ' '),
			pf->dt.width - 1);
	handle_buffer(pf, c);
	if ((pf->dt.param & 1))
		feedbuf_nchar(pf, ' ', pf->dt.width - 1);
	return (1);
}

int	handle_percent(t_pf *pf)
{
	if (!((pf->dt.param & 1)))
		feedbuf_nchar(pf, ft_itrn((pf->dt.param & 010), '0', ' '),
			pf->dt.width - 1);
	handle_buffer(pf, '%');
	if ((pf->dt.param & 1))
		feedbuf_nchar(pf, ' ', pf->dt.width - 1);
	return (1);
}

int	handle_longints(t_pf *pf, va_list ap)
{
	pf->dt.length = 'l';
	if (pf->dt.type == 21)
		pf->dt.type = 2;
	else if (pf->dt.type == 22)
		pf->dt.type = 6;
	else if (pf->dt.type == 23)
		pf->dt.type = 5;
	if (pf->dt.type == 2)
		return (handle_int(pf, ap));
	else
		return (handle_uint(pf, ap));
}
