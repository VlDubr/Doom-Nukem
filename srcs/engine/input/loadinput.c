/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:47:12 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 17:32:26 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static t_input	deserializeinput(char *file)
{
	t_input	r;
	int		y;
	char	**tmp;
	char	**tmp2;

	y = 0;
	tmp = ft_strsplit(file, '\n');
	while (tmp[y] != NULL)
	{
		tmp2 = ft_strsplit(tmp[y], ' ');
		r.input[y] = ft_atoi(tmp2[1]);
		free2dstring(tmp2);
		y++;
	}
	free2dstring(tmp);
	return (r);
}

static void		serializeinput(char *path, t_input input)
{
	int fd;

	fd = open(path, O_CREAT, CREATEFLAG);
	if (fd > -1)
	{
		serializeint(fd, "MoveForward", input.input[MOVEF]);
		serializeint(fd, "MoveBackward", input.input[MOVEB]);
		serializeint(fd, "MoveLeft", input.input[MOVEL]);
		serializeint(fd, "MoveRight", input.input[MOVER]);
		close(fd);
	}
}

static t_input	defaultinput(void)
{
	t_input r;

	r.input[0] = SDLK_w;
	r.input[1] = SDLK_s;
	r.input[2] = SDLK_a;
	r.input[3] = SDLK_d;
	r.mouse.sensivety = 1;
	return (r);
}

void			loadinput(char *path, t_input *input)
{
	char	*fullpath;
	char	*file;

	fullpath = ft_strjoin(path, "config/input.cfg");
	if (!fileexist(fullpath))
	{
		*input = defaultinput();
		serializeinput(fullpath, *input);
	}
	else
	{
		file = readfile(fullpath);
		*input = deserializeinput(file);
		ft_strdel(&file);
	}
	ft_strdel(&fullpath);
}
