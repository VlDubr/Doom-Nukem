/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:47:12 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/31 15:47:20 by gdaniel          ###   ########.fr       */
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
	input.rotup = DSINT(tmp[7], input.rotup);
	input.rotdown = DSINT(tmp[8], input.rotdown);
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
		SINT(fd, input.rotup);
		SINT(fd, input.rotdown);
		close(fd);
	}
}

static t_input	defaultinput(void)
{
	t_input r;

	r.moveforward = SDL_SCANCODE_W;
	r.movebackward = SDL_SCANCODE_S;
	r.moveleft = SDL_SCANCODE_A;
	r.moveright = SDL_SCANCODE_D;
	r.jump = SDL_SCANCODE_SPACE;
	r.rotleft = SDL_SCANCODE_LEFT;
	r.rotright = SDL_SCANCODE_RIGHT;
	r.rotup = SDL_SCANCODE_UP;
	r.rotdown = SDL_SCANCODE_DOWN;
	r.sensivety = 0.0025f;
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
