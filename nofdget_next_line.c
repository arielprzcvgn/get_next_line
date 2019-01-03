/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 12:06:01 by ariperez          #+#    #+#             */
/*   Updated: 2019/01/03 17:00:15 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		readline(int fd, char *buf, char **copy)
{
	int		i;
	char	end;

	end = 0;
	while (end != '\n')
	{
		if (!*buf && (i = read(fd, buf, BUFF_SIZE)) == 0)
			return (0);
		buf[i] = '\0';
		i = 0;
		while (buf[i] != '\n' && buf[i] != '\0')
			i++;
		end = buf[i];
		buf[i] = '\0';
		*copy = ft_strjoinfree(*copy, buf, 1, 0);
		if (end == '\n')
			ft_memmove(buf, (buf + i + 1), BUFF_SIZE - i);
		end == '\n' ? ft_strclr(buf + BUFF_SIZE - i - 1) : ft_strclr(buf);
		if (end != '\n' && (i = read(fd, buf, BUFF_SIZE)) == 0)
			return (1);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char		*buf;
	char			*copy;
	int				ret;

	ret = -1;
	if (fd < 0 || !line || BUFF_SIZE < 0 || read(fd, buf, 0) == -1)
		return (ret);
	if ((copy = ft_strnew(1)) == NULL)
		return (ret);
	if (!buf && !(buf = ft_strnew(BUFF_SIZE + 1)))
		return (ret);
	ret = readline(fd, buf, &copy);
	if (!(*line = ft_strdup(copy)))
		return (-1);
	free(copy);
	return (ret);
}
