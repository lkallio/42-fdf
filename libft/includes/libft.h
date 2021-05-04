/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 06:25:28 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/15 15:05:05 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <inttypes.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include <sys/errno.h>

typedef struct s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct s_strtol
{
	const char		*s;
	unsigned long	num;
	unsigned long	cutoff;
	int				cutlim;
	int				c;
	int				sign;
	int				base;
}					t_strtol;

# define FT_LONGMAX		((unsigned long)0x7FFFFFFF)

char				*ft_strass(char **dst, char *src);
char				*ft_stern(int true, char *s1, char *s2);
int					ft_intass(int *ass, int dst);
int					ft_itrn(int arg, int ret1, int ret2);
int					ft_strpush(char ***strarr_ptr, char *newstr, size_t i);
void				*ft_append(void *addr, size_t new_size, size_t mem_size);
int					ft_strchrn(const char *s, int c);
int					ft_strcjoin(char **dst, char *src, char stop, int count);
char				*ft_strconchr(const char *s, int (*f)(int),
						int truth_value);
int					ft_strconchrlen(const char *s, int (*f)(int),
						int truth_value);
int					ft_strconchrrlen(const char *s, int (*f)(int),
						int truth_value);
char				*ft_strcondup(const char *src, int (*f)(int),
						int truth_value);
char				*ft_strndup(const char *s, int n);
int					ft_iswspace(int c);
int					ft_atoi(const char *str);
void				ft_bzero(void *addr, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memrchr(const void *s, int c, size_t n);
void				*ft_memset(void *str, int c, size_t n);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);
char				*ft_stpncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
void				ft_strclr(char *s);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
void				ft_strdel(char **as);
char				*ft_strdup(const char *src);
int					ft_strequ(char const *s1, char const *s2);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnjoin(char const *s1, char const *s2, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *str);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s1, const char *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *hs, const char *nl, size_t n);
char				*ft_strrchr(const char *str, int c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strstr(const char *hs, const char *nl);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strcdup(char **dst, const char *src, int c, int i);
int					ft_strchrlen(const char *s, int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
int					ft_strstrjoin(char **dst, char *src, char *stop, int count);
void				*ft_realloc(void *addr, size_t old_size,
						size_t size_incr, size_t mem_size);
char				*ft_strex(const char *s, char *p);
long				ft_strtol(const char *s, char **endptr, int base);
void				*ft_ptern(int true, void *p1, void *p2);

#endif
