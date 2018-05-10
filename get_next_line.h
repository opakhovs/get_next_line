/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opakhovs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 16:27:28 by opakhovs          #+#    #+#             */
/*   Updated: 2017/12/24 13:11:49 by opakhovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include "../libft/libft.h"

# define BUFF_SIZE 16

typedef struct	s_fd
{
	int			fd;
	char		*line;
	struct s_fd	*next;
}				t_fd;

int				get_next_line(const int fd, char **line);

#endif
