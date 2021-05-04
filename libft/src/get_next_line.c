/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:36:18 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/14 14:30:48 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	gnl_join(int *ret, char **line, char *portion)
{
	char	*temp;

	if (!*line)
	{
		*line = ft_strnew(0);
		if (!*line)
			return (-1);
	}
	temp = *line;
	*ret = ft_strcjoin(line, portion, '\n', 0);
	free(temp);
	return (*ret);
}

static int	ovride_norm(int *ret, int fd, char *buf)
{
	*ret = read(fd, buf, BUFF_SIZE);
	return (*ret);
}

int	get_next_line(const int fd, char **line)
{
	static char		buf[HANDLE_MAX][BUFF_SIZE + 1];
	int				ret;

	if (!line || fd < 0 || fd > HANDLE_MAX - 1)
		return (-1);
	*line = 0;
	ret = BUFF_SIZE;
	while (buf[fd][0] || ovride_norm(&ret, fd, buf[fd]) > 0)
	{
		buf[fd][ret] = 0;
		if (gnl_join(&ret, line, buf[fd]))
		{
			ft_strcpy(buf[fd], ft_strchr(buf[fd], '\n') + 1);
			return (ret);
		}
		buf[fd][0] = 0;
	}
	if (ret < 0)
		return (ret);
	return (!!*line);
}
