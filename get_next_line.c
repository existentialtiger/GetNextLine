/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edehmlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 21:58:54 by edehmlow          #+#    #+#             */
/*   Updated: 2018/08/07 00:07:22 by edehmlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char		*a[65535] = {0};
	char			*ptr;
	char			*buff;
	char			*temp;

	buff = ft_strnew((size_t)BUFF_SIZE);
	if (read(fd, buff, 0) == -1)
		return (-1);
	if (!a[fd])
	{
		if (!(a[fd] = (char *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
			return (-1);
		if (!read(fd, a[fd], BUFF_SIZE))
			return (0);
	}
	while (!(ptr = ft_strchr(a[fd], '\n')) && read(fd, buff, BUFF_SIZE))
	{
		temp = a[fd];
		if (!(a[fd] = ft_strjoin(a[fd], buff)))
			return (-1);
		ft_strdel(&temp);
	}
	if (ptr)
	{
		if (!(*line = ft_strndup(a[fd], ptr - a[fd])))
			return (-1);
		if (!(*(ptr + 1)))
			ft_strdel(&a[fd]);
		else
		{
			if (!(a[fd] = ft_strdup(ptr + 1)))
				return (-1);
		}
		read(fd, buff, BUFF_SIZE);
		temp = a[fd];
		if (!(a[fd] = ft_strjoin(a[fd], buff)))
			return (2);
		ft_strdel(&temp);
		return (1);
	}
	*line = ft_strdup(a[fd]);
	ft_strdel(&a[fd]);
	return (1);
}
