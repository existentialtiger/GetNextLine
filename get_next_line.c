/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edehmlow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 21:58:54 by edehmlow          #+#    #+#             */
/*   Updated: 2018/08/03 01:21:10 by edehmlow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char		*a[65535];
	char			*ptr;
	char			*buff;

	buff = ft_strnew((size_t)BUFF_SIZE);
	//ft_memalloc a for max fd size?
	if (read(fd, buff, 0) == -1)
		return (-1);
	if (!a[fd])
		read(fd, a[fd], BUFF_SIZE);
	if (a[fd])
	{
		while (!(ptr = ft_strchr(a[fd], '\n')) && read(fd, buff, BUFF_SIZE))
		{
			read(fd, buff, BUFF_SIZE);
			a[fd] = ft_strjoin(a[fd], buff);
		}
		if (ptr = ft_strchr(a[fd], '\n'))
		{
			*line = ft_strndup(a[fd], ptr - buff);
			ptr++;
			a[fd] = ft_strdup(ptr);
			return (1);
		}
		if (read(fd, buff, BUFF_SIZE) == 0)
		{
			free(a[fd]);
			return (0);
		}
	}
	return (0);
}
