/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:39:23 by srafe             #+#    #+#             */
/*   Updated: 2019/05/29 19:42:19 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	loadimages(char *path, char **tmp, t_tga **textures, size_t *count)
{
	int		y;
	char	*filepath;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("sound:", tmp[y])
	&& !ft_strequ("map:", tmp[y]))
		y++;
	(*count) = y;
	(*textures) = (t_tga*)malloc(sizeof(t_tga) * y);
	y = 0;
	while (tmp[y] != NULL && !ft_strequ("sound:", tmp[y])
	&& !ft_strequ("map:", tmp[y]))
	{
		filepath = ft_strjoin(path, tmp[y]);
		(*textures)[y] = *tga_reader(filepath);
		ft_strdel(&filepath);
		y++;
	}
	ft_strdel(&path);
}

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
	return (music);
}

//ft_strjoin(ft_strjoin("Error: ", soundname), " not load")

void	loadsounds(char *path, char **tmp, t_sound *s)
{
	char *t;
	int y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]))
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

void	loadmaps(char *path, char **tmp, t_map **map, size_t *size)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("sound:", tmp[y]))
		y++;
	(*size) = y;
	(*map) = (t_map*)malloc(sizeof(t_map) * y);
	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("sound:", tmp[y]))
	{
		(*map)[y] = loadmap(ft_strjoin(path, tmp[y]));
		y++;
	}
	ft_strdel(&path);
}

void	loadassets(char *path, t_doom *doom)
{
	int		y;
	char	*str;
	char	**tmp;

	y = 0;
	str = readfile(path);
	tmp = ft_strsplit(str, '\n');
	while (tmp[y] != NULL)
	{
		if (ft_strequ("image:", tmp[y]))
			loadimages(ft_strjoin(doom->path, "assets/"), tmp + (y + 1),
			&doom->texture, &doom->texturecount);
		else if (ft_strequ("sound:", tmp[y]))
			loadsounds(ft_strjoin(doom->path, "assets/"), tmp + (y + 1),
			&doom->sound);
		else if (ft_strequ("map:", tmp[y]))
			loadmaps(ft_strjoin(doom->path, "assets/"), tmp + (y + 1),
			&doom->maps, &doom->mapcount);
		y++;
	}
	free2dstring(tmp);
	ft_strdel(&path);
}
