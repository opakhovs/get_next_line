/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opakhovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 16:26:42 by opakhovs          #+#    #+#             */
/*   Updated: 2018/02/06 14:07:41 by opakhovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	t_fd	*ft_getlist(int fd, t_fd **list)
{
	t_fd *temp;

	temp = *list;
	if (!temp)
	{
		temp = (t_fd *)malloc(sizeof(t_fd));
		temp->fd = fd;
		temp->line = ft_memalloc(BUFF_SIZE);
		temp->next = NULL;
		(*list) = temp;
	}
	else
	{
		while (temp)
			if (temp->fd == fd)
				return (temp);
			else
				(temp = temp->next);
		temp = (t_fd *)malloc(sizeof(t_fd));
		temp->fd = fd;
		temp->line = ft_memalloc(BUFF_SIZE);
		temp->next = (*list);
		(*list) = temp;
	}
	return (temp);
}

void			ft_remalloc(t_fd **curr)
{
	char	*temp;

	temp = ft_strnew(ft_strlen((*curr)->line));
	ft_strcpy(temp, (*curr)->line);
	free((*curr)->line);
	(*curr)->line = NULL;
	(*curr)->line = ft_strnew(ft_strlen(temp) + BUFF_SIZE);
	ft_strcpy((*curr)->line, temp);
	free(temp);
	temp = NULL;
}

int				ft_line(char **curr, char **line)
{
	int		i;
	int		y;
	int		size;
	int		check;

	y = 0;
	i = 0;
	size = ft_strlen((*curr));
	while ((*curr)[i] != '\n' && i < size)
		i++;
	*line = ft_strnew(i);
	if (size != 0)
	{
		i = -1;
		while ((*curr)[++i] != '\n' && i < size)
			(*line)[i] = (*curr)[i];
		(*line)[i++] = '\0';
		check = ((*curr)[0] == '\n') ? 1 : 0;
		while (i < size)
			(*curr)[y++] = (*curr)[i++];
		(*curr)[y] = '\0';
		return (check);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static	t_fd	*list;
	char			buff[BUFF_SIZE + 1];
	t_fd			*curr;
	int				count;

	if (fd < 0 || !line || (count = read(fd, buff, 0) < 0))
		return (-1);
	curr = ft_getlist(fd, &list);
	while ((count = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[count] = '\0';
		ft_remalloc(&curr);
		ft_strncat(curr->line, buff, count);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if ((ft_line(&(curr->line), line)) == 1)
		return (1);
	if (**line == '\0')
		return (0);
	return (1);
}
