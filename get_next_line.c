/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edehmlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:00:17 by edehmlow          #+#    #+#             */
/*   Updated: 2018/08/22 16:05:33 by edehmlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	set_line(char **a, char **line, const int fd)
{
	char		*ptr;
	char		*temp;

	if ((ptr = ft_strchr(a[fd], '\n')))
	{
		if (a[fd][0] == *ptr)
			*line = ft_strdup("");
		else
			*line = ft_strndup(a[fd], ptr - a[fd]);
		ptr++;
		temp = a[fd];
		a[fd] = ft_strdup(ptr);
		ft_strdel(&temp);
		return (1);
	}
	else if (a[fd][0] != '\0')
	{
		*line = ft_strdup(a[fd]);
		ft_strdel(&a[fd]);
		return (1);
	}
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	static char	*a[FD_MAX];
	char		buff[BUFF_SIZE + 1];
	int			chk;
	char		*temp;

	if (fd > FD_MAX || fd < 0 || !line)
		return (-1);
	ft_bzero(buff, BUFF_SIZE + 1);
	if (!a[fd])
	{
		if (!(a[fd] = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
	}
	while ((chk_for_char(a[fd], '\n') < 0) && (chk = read(fd, buff, BUFF_SIZE)))
	{
		if (chk < 0)
			return (-1);
		temp = a[fd];
		a[fd] = ft_strjoin(a[fd], buff);
		ft_strdel(&temp);
		ft_bzero(buff, BUFF_SIZE);
	}
	if (set_line(a, line, fd))
		return (1);
	return (0);
}
