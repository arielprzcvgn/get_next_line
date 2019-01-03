/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariperez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 12:06:01 by ariperez          #+#    #+#             */
/*   Updated: 2019/01/03 18:30:29 by ariperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*fd_choice(int fd, t_list *file)
{
	t_list	*begin;
	char	*buf;

	if (!(buf = ft_strnew(BUFF_SIZE + 1)))
		return (NULL);
	if (!file && ((!(file = malloc(sizeof(t_list)))) ||
		!(file->content = buf) ||
		!(file->content_size = (size_t)fd) ||
		!(file->next = file)))
		return (NULL);
	begin = file;
	while ((size_t)fd != file->content_size)
	{
		file = file->next;
		if (file == begin)
		{
			if (!(file = malloc(sizeof(t_list))))
				return (NULL);
			file->content = buf;
			file->content_size = (size_t)fd;
			file->next = begin->next;
			begin->next = file;
			return (file);
		}
	}
	return (file);
}

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
	static t_list	*file;
	char			*copy;
	int				ret;

	ret = -1;
	if (fd < 0 || !(copy = ft_strnew(1)) || read(fd, copy, 0) == -1 ||
		BUFF_SIZE < 0 || !line || !(file = fd_choice(fd, file)))
		return (ret);
	ret = readline((int)file->content_size, file->content, &copy);
	if (!(*line = ft_strdup(copy)))
		return (-1);
	free(copy);
	return (ret);
}
