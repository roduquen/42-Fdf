/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 15:45:10 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/03 16:43:42 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_read_buff(const int fd, char *buffer)
{
	int ret;
	int	newret;

	if (!(buffer = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (NULL);
	newret = 0;
	buffer[newret] = 0;
	while ((ret = read(fd, buffer + newret, BUFF_SIZE)) > 0)
	{
		newret += ret;
		buffer[newret] = 0;
		if (buffer[ft_strlendl(buffer)] == '\n')
			break ;
		else if (!(buffer = ft_realloc(buffer, newret + BUFF_SIZE + 1)))
		{
			free_ptr(buffer);
			return (NULL);
		}
	}
	if (ret < 0)
	{
		free_ptr(buffer);
		return (NULL);
	}
	return (buffer);
}

static int	get_next_line3(t_list *begin_list, t_list *current, char **line
	, size_t i)
{
	char	*buff;

	while (((char*)current->content)[i] && ((char*)current->content)[i] != '\n')
		i++;
	if (!(buff = ft_strsub(current->content, i + 1
				, ft_strlen(current->content) - i)))
		return (-1);
	if (!(*line = ft_strsub(current->content, 0, i)))
		return (-1);
	if (!buff[0])
	{
		while (begin_list->next != current)
			begin_list = begin_list->next;
		begin_list->next = current->next;
		free_ptr(current->content);
		free_ptr(current);
		free_ptr(buff);
	}
	else
	{
		free_ptr(current->content);
		current->content = ft_strdup(buff);
		free_ptr(buff);
	}
	return (1);
}

static int	get_next_line2(t_list *begin_list, t_list *current, char **line
	, int fd)
{
	size_t		i;
	char		*buffer;
	char		*tmp;

	i = 0;
	if (((char*)current->content)[ft_strlendl((char*)current->content)] == 0)
	{
		buffer = NULL;
		if ((buffer = ft_read_buff(fd, buffer)))
		{
			if (!(tmp = ft_strjoin(current->content, buffer)))
				return (-1);
			free_ptr(current->content);
			current->content = tmp;
			free_ptr(buffer);
		}
		else
		{
			free_ptr(current->content);
			free_ptr(current);
			return (0);
		}
	}
	return (get_next_line3(begin_list, current, line, 0));
}

static int	create_new_elem(t_list *begin_list, t_list *current, const int fd
		, char **line)
{
	char	*buffer;

	buffer = NULL;
	if (!(buffer = ft_read_buff(fd, buffer)))
		return (-1);
	if (!buffer[0])
	{
		free_ptr(buffer);
		return (0);
	}
	if (!(current->next = ft_lstnew(buffer, ft_strlen(buffer) + 1)))
	{
		free_ptr(buffer);
		return (-1);
	}
	current->next->content_size = fd;
	free_ptr(buffer);
	return (get_next_line2(begin_list, current->next, line, fd));
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*begin_list;
	t_list			*current;

	if (fd == -1 || !line)
		return (-1);
	if (!begin_list)
	{
		if (!(begin_list = ft_lstnew("Beginning", 10)))
			return (-1);
	}
	current = begin_list;
	while (current->next && current->next->content_size != (size_t)fd)
		current = current->next;
	if (current->next)
		return (get_next_line2(begin_list, current->next, line, fd));
	return (create_new_elem(begin_list, current, fd, line));
}
