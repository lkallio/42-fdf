/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_ints.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:45 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 16:11:06 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	int_length(t_pf *pf, va_list ap)
{
	if (pf->dt.length == 'l')
		return (va_arg(ap, long));
	else if (pf->dt.length == 'l' + 'l')
		return (va_arg(ap, long long));
	else if (pf->dt.length == 'z')
		return (va_arg(ap, size_t));
	else if (pf->dt.length == 'j')
		return (va_arg(ap, intmax_t));
	else if (pf->dt.length == 'h')
		return ((short)va_arg(ap, int));
	else if (pf->dt.length == 'h' + 'h')
		return ((char)va_arg(ap, int));
	else
		return (va_arg(ap, int));
}

static uintmax_t	uint_length(t_pf *pf, va_list ap)
{
	if (pf->dt.length == 'l')
		return (va_arg(ap, unsigned long));
	else if (pf->dt.length == 'l' + 'l')
		return (va_arg(ap, unsigned long long));
	else if (pf->dt.length == 'z')
		return (va_arg(ap, size_t));
	else if (pf->dt.length == 'j')
		return (va_arg(ap, uintmax_t));
	else if (pf->dt.length == 'h')
		return ((unsigned short)va_arg(ap, int));
	else if (pf->dt.length == 'h' + 'h')
		return ((unsigned char)va_arg(ap, int));
	else
		return (va_arg(ap, unsigned int));
}

int	handle_ptr(t_pf *pf, va_list ap)
{
	pf->dt.param |= (1 << 4);
	pf->dt.type = 7;
	pf->dt.length = 'l';
	pf->dt.param |= (1 << 6);
	return (handle_uint(pf, ap));
}

int	handle_int(t_pf *pf, va_list ap)
{
	intmax_t	in;

	in = int_length(pf, ap);
	pf->dt.width -= ((pf->dt.param & 2) || (pf->dt.param & 4) || in < 0);
	if (in < 0)
	{
		pf->dt.param |= (1 << 5);
		in *= -1;
	}
	write_int(in, pf, 10, 0);
	if ((pf->dt.param & 1))
		feedbuf_nchar(pf, ' ', pf->dt.width - pf->dt.num_len);
	return (1);
}

int	handle_uint(t_pf *pf, va_list ap)
{
	uintmax_t	in;

	in = uint_length(pf, ap);
	if (((pf->dt.type == 7 || pf->dt.type == 8) && !in && !(pf->dt.param
				& (1 << 6)))
		|| (pf->dt.type == 6 && !in && pf->dt.prec))
		pf->dt.param &= ~((pf->dt.param & 020));
	if (pf->dt.type > 5 && (pf->dt.param & 020))
		pf->dt.width -= (pf->dt.type > 6) + 1;
	if (pf->dt.type == 6 && pf->dt.prec > 0 && (pf->dt.param & 020))
		pf->dt.prec -= 1;
	if (pf->dt.type == 6 || pf->dt.type == 7 || pf->dt.type == 8)
		write_int(in, pf, 16 - (pf->dt.type == 6) * 8, 0);
	else
		write_int(in, pf, 10 - (pf->dt.type == 9 || pf->dt.type == 10) * 8, 0);
	if ((pf->dt.param & 1))
		feedbuf_nchar(pf, ' ', pf->dt.width - pf->dt.num_len);
	return (1);
}
