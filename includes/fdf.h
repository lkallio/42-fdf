/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:51:59 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/18 14:06:39 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"

typedef struct s_keyev
{
	int							key;
	struct	s_mtx				*(*m)(void);
	float						by;
	int							flag;
}								t_keyev;

typedef struct s_color
{
	float						r;
	float						g;
	float						b;
}								t_color;

typedef struct s_vtx
{
	float						v[4];
	t_color						color;
}								t_vtx;

typedef struct s_vtxl
{
	t_vtx						v;
	t_vtx						t;
	struct s_vtxl				*next;
	struct s_vtxl				*rnext;
	struct s_vtxl				*cnext;
	unsigned					unused : 2;
}								t_vtxl;

typedef struct s_dim
{
	float						xmax;
	float						zmax;
	float						ymax;
	float						ymin;
	float						yabsmax;
	float						allmax;
}								t_dim;

typedef struct s_img
{
	void						*ip;
	char						*buf;
	char						*zvals;
	size_t						buf_size;
	size_t						zvals_size;
	int							bpp;
	int							sl;
	int							end;
}								t_img;

typedef struct s_mlx
{
	void						*m;
	void						*w;
}								t_mlx;

typedef struct s_args
{
	int							flags;
	int							color;
	int							bcol;
}								t_args;

typedef struct s_draw
{
	int							step;
	int							var;
	float						err[3];
	float						steps[3];
	t_color						col_gradient;
}								t_draw;

typedef struct s_mtx
{
	t_vtx						m[4];
}								t_mtx;

typedef struct s_readvtcs
{
	t_vtxl						*cur;
	t_vtx						pos;
	int							i;
}								t_readvtcs;

typedef struct s_getargs
{
	int							flag;
	char						*arg;
}								t_getargs;

# define WIN_W					900
# define WIN_H					700
# define IMG_W					WIN_W
# define IMG_H					WIN_H

# if WIN_W < 900
#  define FDF_NOSTRDEFAULT		0b10000000000
# else
#  define FDF_NOSTRDEFAULT		0
# endif

# define FDF_ORTH				0b10
# define FDF_COLOR				0b100
# define FDF_DEFAULTOPT			0b1000
# define FDF_FORCEOPT			0b10000
# define FDF_OPT				0b11000
# define FDF_DEFAULTGRAD		0b100000
# define FDF_FORCEGRAD			0b1000000
# define FDF_GRAD				0b1100000
# define FDF_CAMERA				0b10000000
# define FDF_NOISO				0b100000000
# define FDF_BCOL				0b1000000000
# define FDF_NOSTR				0b10000000000
# define FDF_VERB				0b100000000000

# define UD_RX					1
# define UD_RY					0b10
# define UD_RZ					0b100
# define UD_ROT					0b111
# define UD_TX					0b1000
# define UD_TY					0b10000
# define UD_TZ					0b100000
# define UD_TRANS				0b111000
# define UD_ZI					0b1000000
# define UD_ZO					0b10000000
# define UD_FPS					0b100000000

# define X_AX					0b001
# define Y_AX					0b010
# define Z_AX					0b100
# define K_LEFT					0xff51
# define K_RIGHT				0xff53
# define K_DOWN					0xff54
# define K_UP					0xff52
# define K_W					0x77
# define K_S					0x73
# define K_A					0x61
# define K_D					0x64
# define K_Q					0x65
# define K_E					0x71
# define K_ESC					0xff1b
# define K_Z					0x7a
# define K_X					0x78

# define P_FOV					0.8976f
# define P_FAR					50.0f
# define P_NEAR					0.1f

void							set_pix(int x, int y, float z, t_color color);
int								col_grad(int sc, int ec, float p);
void							set_line(t_vtx start, t_vtx end);
void							feed_vtcs(t_vtx start, t_vtx end);
void							vtclst_to_img(t_vtxl *cur);

t_mtx							*m_additional(void);

t_mlx							*get_mw(void);
t_img							*get_img(void);
t_dim							*get_dim(void);
t_args							*get_args(void);

void							new_frame(t_vtxl *vtcs);
int								keyev(int kc, t_vtxl *vtcs);
int								pointerev(int x, int y, t_vtxl *vtcs);

int								main(int ac, char **av);
void							fdf_usage(void);

t_mtx							*m_view(void);
t_mtx							*m_proj(void);
t_mtx							*m_world(void);
void							update(t_mtx *m, float a, int flag);
t_mtx							model_to_screen(void);
void							mul_all(t_vtxl *cur, t_mtx m, int apply);

t_mtx							m_idty(void);
t_mtx							m_xrot(float a);
t_mtx							m_yrot(float a);
t_mtx							m_zrot(float a);
t_mtx							m_trans(float x, float y, float z);
t_mtx							m_scale(float x, float y, float z);
t_vtx							v_mul(t_vtx vtx, t_mtx mtx);
t_mtx							m_mul(t_mtx s, t_mtx d);

t_vtxl							*lookaheadr(t_vtxl *start);
t_vtxl							*lookaheadc(t_vtxl *start);
t_readvtcs						*get_last(void);
t_vtxl							*vtxl_node(t_vtxl *ret, t_vtx pos);
t_color							get_color(char *inp, int i);
t_vtxl							*read_vtcs(char *inp, t_vtx pos, int i, int *r);
void							connect_nodes(t_vtxl *cur);
t_vtxl							*read_vtcs_chunks(char *inp);
void							remove_unused_vtcs(t_vtxl *cur);
void							sig_color(t_vtxl *cur);
void							data_setup(t_vtxl *vtcs);
t_dim							*init_dim(void);

#endif
