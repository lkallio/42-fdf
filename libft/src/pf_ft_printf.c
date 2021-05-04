/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_ft_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:31 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 17:00:15 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_type(t_pf *pf, va_list ap)
{
	if (pf->dt.type == 1)
		handle_n(pf, ap);
	else if (pf->dt.type == 0)
		handle_percent(pf);
	else if (pf->dt.type >= 2 && pf->dt.type <= 3)
		handle_int(pf, ap);
	else if (pf->dt.type == 4)
		handle_c(pf, ap);
	else if (pf->dt.type >= 5 && pf->dt.type <= 10)
		handle_uint(pf, ap);
	else if (pf->dt.type == 11)
		handle_str(pf, ap);
	else if (pf->dt.type == 12)
		handle_ptr(pf, ap);
	else if (pf->dt.type >= 13 && pf->dt.type <= 20)
		handle_double(pf, ap);
	else if (pf->dt.type >= 21)
		handle_longints(pf, ap);
}

static void	parse_options(t_pf *pf, int *i, va_list ap, int cont)
{
	int		ret;

	if (!cont--)
		return ;
	while (ft_intass(&ret, ft_nstrchr("-+ 0#", pf->format[(*i)])) != -1
		&& ++(*i))
	{
		cont = 1;
		pf->dt.param |= 1 << ret;
	}
	if (((pf->format[(*i)] >= '0' && pf->format[(*i)] <= '9')
			|| pf->format[(*i)] == '*') && ft_intass(&cont, 1))
		pf->dt.width = ft_itrn(pf->format[(*i)] == '*' && ++(*i),
				va_arg(ap, int), pf_atoi(pf, i, 0));
	if (pf->format[(*i)] == '.' && ++(*i) && ft_intass(&cont, 1))
		pf->dt.prec = pf_atoi(pf, i, 0);
	if (ft_intass(&ret, ft_nstrchr("hlLzjt", pf->format[(*i)])) != -1)
	{
		cont = 1;
		pf->dt.length = pf->format[(*i)++];
		if ((pf->dt.length == 'h' && pf->format[(*i)] == 'h')
			|| (pf->dt.length == 'l' && pf->format[(*i)] == 'l'))
			pf->dt.length += pf->format[(*i)++];
	}
	parse_options(pf, i, ap, cont);
}

static void	parse_argument(t_pf *pf, int *i, va_list ap)
{
	int	ret;

	++(*i);
	parse_options(pf, i, ap, 1);
	if (ft_intass(&ret, ft_nstrchr("%ndicuoxXbBspfFgGeEaADOU",
				pf->format[(*i)])) != -1 && ++(*i))
	{
		pf->dt.type = ret;
		handle_type(pf, ap);
	}
}

static int	parse_quoted(t_pf *pf, va_list ap)
{
	int		i;
	int		j;

	i = 0;
	while (pf->format[i])
	{
		if (pf->format[i] == '%')
		{
			j = -1;
			pf->dt = (t_dt){0, -1, -1, 0, 0, 0, 0};
			parse_argument(pf, &i, ap);
			continue ;
		}
		handle_buffer(pf, pf->format[i++]);
	}
	write(1, pf->buf, pf->buf_idx);
	return (1);
}

int	ft_printf(char const *format, ...)
{
	t_pf	pf;
	va_list	ap;

	va_start(ap, format);
	pf = (t_pf){.dt = {0, -1, -1, 0, 0, 0, 0}, .buf = {0},
		.buf_idx = 0, .n = 0, .format = format, .tempstr = 0};
	parse_quoted(&pf, ap);
	va_end(ap);
	return (pf.n + pf.buf_idx);
}
