/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:39:23 by srafe             #+#    #+#             */
/*   Updated: 2019/04/25 15:21:02 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	loadimage(char **tmp)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("sound:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("music:", tmp[y]))
		y++;
}

void	loadsound(char *path, char **tmp, t_doom *doom)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("music:", tmp[y]))
		y++;
	doom->sounds->samples = (Mix_Chunk	**)malloc(sizeof(Mix_Chunk	*) * y);
	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("music:", tmp[y]))
	{
		doom->sounds->samples[y] = Mix_LoadWAV(ft_strjoin(path, tmp[y]));
		y++;
	}
	Mix_AllocateChannels(5);
	Mix_Volume(-1, 64);
}

void	loadmusic(char *path, char **tmp, t_doom *doom)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("sound:", tmp[y]))
		y++;
	doom->sounds->game = (Mix_Music	**)malloc(sizeof(Mix_Music	*) * y);
	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("sound:", tmp[y]))
	{
		doom->sounds->game[y] = Mix_LoadMUS(ft_strjoin(path, tmp[y]));
		y++;
	}
	Mix_VolumeMusic(64);
}

void	loadmaps(char *path, char **tmp, t_map **map, size_t *size)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("sound:", tmp[y]) && !ft_strequ("music:", tmp[y]))
		y++;
	(*size) = y;
	(*map) = (t_map*)malloc(sizeof(t_map) * y);
	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("sound:", tmp[y]) && !ft_strequ("music:", tmp[y]))
	{
		(*map)[y] = loadmap(ft_strjoin(path, tmp[y]));
		y++;
	}
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
			loadimage(tmp + (y + 1));
		else if (ft_strequ("sound:", tmp[y]))
			loadsound(ft_strjoin(doom->path, "assets/"), tmp + (y + 1), doom);
		else if (ft_strequ("music:", tmp[y]))
			loadmusic(ft_strjoin(doom->path, "assets/"), tmp + (y + 1), doom);
		else if (ft_strequ("map:", tmp[y]))
			loadmaps(ft_strjoin(doom->path, "assets/"), tmp + (y + 1),
			&doom->maps, &doom->mapcount);
		y++;
	}
}
