/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:47:12 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 12:39:45 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static t_input	deserializeinput(char *file)
{
	t_input	input;
	int		y;
	char	**tmp;
	char	*name;

	y = 0;
	tmp = ft_strsplit(file, '\n');
	input.moveforward = DSINT(tmp[0], input.moveforward);
	input.movebackward = DSINT(tmp[1], input.movebackward);
	input.moveleft = DSINT(tmp[2], input.moveleft);
	input.moveright = DSINT(tmp[3], input.moveright);
	input.jump = DSINT(tmp[4], input.jump);
	input.rotleft = DSINT(tmp[5], input.rotleft);
	input.rotright = DSINT(tmp[6], input.rotright);
	free2dstring(tmp);
	return (input);
}

static void		serializeinput(char *path, t_input input)
{
	int fd;

	fd = open(path, O_CREAT | O_WRONLY, CREATEFLAG);
	if (fd > -1)
	{
		SINT(fd, input.moveforward);
		SINT(fd, input.movebackward);
		SINT(fd, input.moveleft);
		SINT(fd, input.moveright);
		SINT(fd, input.jump);
		SINT(fd, input.rotleft);
		SINT(fd, input.rotright);
		close(fd);
	}
}

static t_input	defaultinput(void)
{
	t_input r;

	r.moveforward = SDLK_w;
	r.movebackward = SDLK_s;
	r.moveleft = SDLK_a;
	r.moveright = SDLK_d;
	r.jump = SDLK_SPACE;
	r.rotleft = SDLK_LEFT;
	r.rotright = SDLK_RIGHT;
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
