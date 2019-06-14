/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:39:23 by srafe             #+#    #+#             */
/*   Updated: 2019/06/14 12:41:59 by gdaniel          ###   ########.fr       */
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

void		loadassets2(char *path, t_doom *doom, char *str)
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
	doom->music = loadmusic(ft_strjoin(path, "ost.mp3"));
	ft_strdel(&path);
	ft_strdel(&str);
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
	loadassets2(ft_strjoin(doom->path, "assets/"), doom, str);
	free2dstring(tmp);
}
