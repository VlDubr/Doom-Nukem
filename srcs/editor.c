/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:19:38 by srafe             #+#    #+#             */
/*   Updated: 2019/05/15 14:48:25 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	ft_error(const char *str)
{
	ft_putendl(str);
	exit(-1);
}

char	*file_read(int fd)
{
	char	*buf;
	char	*str;
	int		j;

	buf = (char *)malloc(sizeof(char) * 1000);
	str = malloc(0);

	if (fd == -1)
		ft_error("error");
	while ((j = read(fd, buf, 1000)) > 0)
	{
		buf[j] = '\0';
		str = ft_strjoin(str, buf);
	}
	return (str);
}

void	editor(char *path)
{
	int		fd;
	char	*str;
	t_service s;
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	fd = open(path, O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
	str = file_read(fd);
	map_parser(&s, str, map);
	//str = ft_strjoin(str, "ddddd\naaa");
	//write(fd, str, sizeof(char) * ft_strlen(str));
	close(fd);
}
