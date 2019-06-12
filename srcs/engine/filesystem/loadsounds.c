/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsounds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:24:05 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:29:39 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

Mix_Chunk	*loadsound(char *path, char *soundname)
{
	size_t		i;
	size_t		len;
	char		*p;
	Mix_Chunk	*music;

	len = ft_strlen(path);
	i = len;
	while (path[i] != '/')
		i--;
	i++;
	p = ft_strsub(path, i, ft_strlen(soundname));
	music = NULL;
	if (ft_strequ(p, soundname))
	{
		music = Mix_LoadWAV(path);
		if (music == NULL)
			error(Mix_GetError());
	}
	ft_strdel(&p);
	return (music);
}

void		loadsounds(char *path, char **tmp, t_sound *s)
{
	char	*t;
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("weapons:", tmp[y]))
	{
		t = ft_strjoin(path, tmp[y]);
		if (ft_strequ(tmp[y], "sounds/jump.mp3"))
			s->jump = loadsound(t, "jump.mp3");
		else if (ft_strequ(tmp[y], "sounds/damage.mp3"))
			s->run = loadsound(t, "damage.mp3");
		else if (ft_strequ(tmp[y], "sounds/shot.mp3"))
			s->shot = loadsound(t, "shot.mp3");
		ft_strdel(&t);
		y++;
	}
}
