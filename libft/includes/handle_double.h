/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:51:51 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 17:11:03 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_DOUBLE_H
# define HANDLE_DOUBLE_H

# include "ft_printf.h"

typedef struct s_dbl_dt
{
	int				base;
	int				opt;
	int				pos_exp;
	int				neg_exp;
	int				boolean;
	int				mts_len;
	int				whl_len;
}	t_dbl_dt;

typedef struct s_dbl
{
	long double				in[2];
	t_dbl_dt				dt;
	char					*whole;
	char					*mantissa;
}	t_dbl;

void						dbl_get_data(t_pf *pf, t_dbl *dbl);
void						write_dbl(t_pf *pf, t_dbl *dbl);
int							dbl_hex_char(t_pf *pf, t_dbl *dbl, int num);
int							handle_double(t_pf *pf, va_list ap);

#endif
