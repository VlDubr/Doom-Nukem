/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:39:23 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 12:38:30 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		loadimages(char *path, char **tmp, t_tga **textures, size_t *count)
{
	int		y;
	char	*filepath;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("sound:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("weapons:", tmp[y]))
		y++;
	(*count) = y;
	(*textures) = (t_tga*)malloc(sizeof(t_tga) * y);
	y = 0;
	while (tmp[y] != NULL && !ft_strequ("sound:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("weapons:", tmp[y]))
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

void		loadmaps(char *path, char **tmp, t_map **map, size_t *size)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("sound:", tmp[y]) && !ft_strequ("weapons:", tmp[y]))
		y++;
	(*size) = y;
	(*map) = (t_map*)malloc(sizeof(t_map) * y);
	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("sound:", tmp[y]) && !ft_strequ("weapons:", tmp[y]))
	{
		(*map)[y] = loadmap(ft_strjoin(path, tmp[y]));
		y++;
	}
	ft_strdel(&path);
}

void		loadweapontexture(t_weapon **weapon, size_t count, t_doom *doom)
{
	size_t		i;
	t_ivector	wh;
	t_tga		*texture;
	t_tga		**frame;
	int			framemax;

	i = 0;
	while (i < count)
	{
		wh = (*weapon)[i].imagetype;
		texture = &doom->texture[(*weapon)[i].imageid];
		if (wh.x == 1)
		{
			frame = bitmap_mall(texture,
			setivector2d(wh.y, wh.z), &framemax);
			(*weapon)[i].anim = setanim(frame, framemax);
			(*weapon)[i].texture = *frame;
		}
		else
			(*weapon)[i].texture[0] = *texture;
		i++;
	}
}

void		loadfont(char *path, t_doom *doom)
{
	char *p;

	p = ft_strjoin(path, "font.tga");
	doom->font = bitmap(p, setivector2d(28, 36));
	ft_strdel(&p);
	ft_strdel(&path);
}

t_tga		*loadsecontimage(char *path)
{
	t_tga	*image;

	image = tga_reader(path);
	ft_strdel(&path);
	return (image);
}

void		loadassets2(char *path, t_doom *doom)
{
	loadfont(ft_strjoin(doom->path, "assets/"), doom);
	loadweapontexture(&doom->weapons, doom->weaponcount, doom);
	doom->skybox = loadsecontimage(ft_strjoin(path, "skybox.tga"));
	doom->door = loadsecontimage(ft_strjoin(path, "door.tga"));
	doom->logo = loadsecontimage(ft_strjoin(path, "logo.tga"));
	doom->gameoverlogo = loadsecontimage(ft_strjoin(path, "gameoverlogo.tga"));
	doom->newgametga = loadsecontimage(ft_strjoin(path, "newgame.tga"));
	doom->quittga = loadsecontimage(ft_strjoin(path, "quit.tga"));
	doom->easytga = loadsecontimage(ft_strjoin(path, "easy.tga"));
	doom->middletga = loadsecontimage(ft_strjoin(path, "middle.tga"));
	doom->hardtga = loadsecontimage(ft_strjoin(path, "hard.tga"));
	ft_strdel(&path);
}

void		loadassets(char *path, t_doom *doom)
{
	int		y;
	char	*str;
	char	**tmp;

	y = -1;
	str = readfile(path);
	ft_strdel(&path);
	tmp = ft_strsplit(str, '\n');
	while (tmp[++y] != NULL)
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
		else if (ft_strequ("weapons:", tmp[y]))
			loadweapons(ft_strjoin(doom->path, "assets/"), tmp + (y + 1),
			&doom->weapons, &doom->weaponcount);
	}
	loadassets2(ft_strjoin(doom->path, "assets/"), doom);
	free2dstring(tmp);
	ft_strdel(&str);
}
