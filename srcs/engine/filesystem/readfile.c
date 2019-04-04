/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 16:03:48 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 16:08:43 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filesystem.h"

char	*readfile(char *path)
{
	char	*str;
	char	*del;
	char	buff[BUFF_SIZE + 1];
	int		fd;
	int		r;

	fd = open(path, O_RDONLY);
	str = ft_strnew(0);
	while ((r = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[r] = '\0';
		del = str;
		str = ft_strjoin(str, buff);
		ft_strdel(&del);
	}
	return (str);
}
