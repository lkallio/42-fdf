/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:18 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/15 15:50:39 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_getargs	*getgetargs(void)
{
	static t_getargs	args[] = {
		{.arg = "--orthographic", .flag = FDF_ORTH},
		{.arg = "--color=(*)", .flag = FDF_COLOR},
		{.arg = "--optimize", .flag = FDF_FORCEOPT},
		{.arg = "--no-optimize", .flag = (FDF_DEFAULTOPT | 1)},
		{.arg = "--no-gradient", .flag = (FDF_DEFAULTGRAD | 1)},
		{.arg = "--gradient", .flag = FDF_FORCEGRAD},
		{.arg = "--camera-view", .flag = FDF_CAMERA},
		{.arg = "--no-iso", .flag = FDF_NOISO},
		{.arg = "--background-color=(*)", .flag = FDF_BCOL},
		{.arg = "--no-instructions", .flag = FDF_NOSTR},
		{.arg = "--verbose", .flag = FDF_VERB},
		{0}
	};

	return (args);
}

static char	*check_args(char **av)
{
	int					i;
	static t_getargs	*args;

	if (!args)
		args = getgetargs();
	if (!*av)
		fdf_usage();
	if ((*av)[0] != '-')
		return (*av);
	i = -1;
	while (args[++i].flag)
	{
		if (!ft_strex(*av, args[i].arg))
			continue ;
		if (args[i].flag == FDF_COLOR)
			get_args()->color = ft_strtol(ft_strex(0, 0), 0, 0);
		if (args[i].flag == FDF_BCOL)
			get_args()->bcol = ft_strtol(ft_strex(0, 0), 0, 0);
		get_args()->flags = ft_itrn((args[i].flag & 1),
			get_args()->flags & ~args[i].flag,
			get_args()->flags | args[i].flag);
		return (check_args(av + 1));
	}
	fdf_usage();
	return (0);
}

void	fdf_usage(void)
{
	t_getargs	*args;

	if (errno)
		ft_printf("%s\n", strerror(errno));
	else
	{
		args = getgetargs();
		ft_printf("usage: ./fdf [options ...] [file]\n\
	available options:\n");
		while (args->flag)
			ft_printf("\t\t%s\n", args++->arg);
	}
	exit(1);
}

int	main(int ac, char **av)
{
	t_vtxl		*vtcs;
	char		*file_str;

	ac++;
	file_str = ft_filetostr(open(check_args(av + 1), O_RDONLY));
	vtcs = read_vtcs_chunks(file_str);
	data_setup(vtcs);
	new_frame(vtcs);
	mlx_hook(get_mw()->w, 2, 1 | 2, keyev, vtcs);
	mlx_loop(get_mw()->m);
	return (0);
}
