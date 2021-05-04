/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyev.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 13:36:15 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/15 15:07:39 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_frame(void *buf, ssize_t size, int is_img)
{
	static int			bcol_orig = -1;
	register long long	bcol;
	register long long	*subject;
	register ssize_t	i;

	if (bcol_orig == -1)
		bcol_orig = get_args()->bcol;
	bcol = ((long long)bcol_orig << 32)
		| (long long)bcol_orig;
	subject = (long long *)buf;
	i = size;
	if (is_img)
	{
		while (i--)
			if (subject[i] != bcol)
				subject[i] = bcol;
	}
	else
	{
		while (i--)
			if (subject[i])
				subject[i] &= 0;
	}
}

static void	put_controls(void)
{
	static char		*controls[] = {
		"rotation: [w] [a] [s] [d] [q] [e]",
		"move: arrow keys",
		"zoom/scale: [z] [x]",
		"exit: [esc]"};
	static int		stringcol = -1;
	int				y;
	int				i;

	if (stringcol == -1)
		stringcol = get_args()->bcol ^ 0xffffff;
	i = -1;
	y = (int)((float)IMG_H * 0.1f);
	while (++i < 4)
	{
		y += 20;
		mlx_string_put(get_mw()->m, get_mw()->w,
			(int)((float)IMG_W * 0.75f), y, stringcol,
			controls[i]);
	}
}

void	new_frame(t_vtxl *vtcs)
{
	mul_all(vtcs, model_to_screen(), 0);
	clear_frame(get_img()->buf, get_img()->buf_size, 1);
	clear_frame(get_img()->zvals, get_img()->zvals_size, 0);
	vtclst_to_img(vtcs);
	mlx_put_image_to_window(get_mw()->m,
		get_mw()->w, get_img()->ip, 0, 0);
	if (!(get_args()->flags & FDF_NOSTR))
		put_controls();
}

static t_keyev	*get_keyev(void)
{
	static t_keyev	v[] = {
		{.key = K_S, .by = M_PI / 64.0f, .flag = UD_RX},
		{.key = K_W, .by = -M_PI / 64.0f, .flag = UD_RX},
		{.key = K_A, .by = M_PI / 64.0f, .flag = UD_RY},
		{.key = K_D, .by = -M_PI / 64.0f, .flag = UD_RY},
		{.key = K_Q, .by = -M_PI / 64.0f, .flag = UD_RZ},
		{.key = K_E, .by = M_PI / 64.0f, .flag = UD_RZ},
		{.key = K_UP, .by = 0.02f, .flag = UD_TY},
		{.key = K_DOWN, .by = -0.02f, .flag = UD_TY},
		{.key = K_LEFT, .by = 0.02f, .flag = UD_TX},
		{.key = K_RIGHT, .by = -0.02f, .flag = UD_TX},
		{.key = K_Z, .by = -0.05f, .flag = UD_TZ},
		{.key = K_X, .by = 0.05f, .flag = UD_TZ}
	};

	return (v);
}

int	keyev(int kc, t_vtxl *vtcs)
{
	int				i;
	static t_keyev	*v;
	static t_mtx	*m;

	if (kc == K_ESC)
		exit(0);
	if (!v)
		v = get_keyev();
	if (!m)
		m = (t_mtx *)ft_ptern((get_args()->flags & FDF_CAMERA),
				m_view(), m_world());
	i = -1;
	while (++i < 12)
	{
		if (kc == v[i].key)
		{
			update(m, v[i].by, v[i].flag);
			new_frame(vtcs);
			break ;
		}
	}
	return (1);
}
