/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:39:23 by srafe             #+#    #+#             */
/*   Updated: 2019/04/25 16:43:24 by srafe            ###   ########.fr       */
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
	Mix_Volume(-1, 96);
}

void	loadmusic(char *path, char **tmp, t_doom *doom)
{
	int		y;
	int		flag;
	char	*del;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("sound:", tmp[y]))
		y++;
	doom->sounds->game_mus = (Mix_Music	**)malloc(sizeof(Mix_Music	*) * y);
	doom->sounds->menu = (Mix_Music	**)malloc(sizeof(Mix_Music	*) * y);
	y = 0;
	flag = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]) && !ft_strequ("sound:", tmp[y]))
	{
		if (ft_strstr(tmp[y], "menu") != NULL)
		{
			doom->sounds->menu[flag] = Mix_LoadMUS(ft_strjoin(path, tmp[y]));
			flag++;
		}
		else
			doom->sounds->game_mus[y - flag] =
				Mix_LoadMUS(del = ft_strjoin(path, tmp[y]));
		y++;
		free(del);
	}
	doom->sounds->music_count = y - flag;
	Mix_VolumeMusic(32);
}

void	loadmaps(char *path, char **tmp, t_map **map, size_t *size)
{
	int		y;
	char	*del;

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
		del = ft_strjoin(path, tmp[y]);
		(*map)[y] = loadmap(del);
		y++;
		free(del);
	}
}

void	loadassets(char *path, t_doom *doom)
{
	int		y;
	char	*str;
	char	**tmp;
	char	*del;

	y = 0;
	str = readfile(path);
	tmp = ft_strsplit(str, '\n');
	while (tmp[y] != NULL)
	{
		if (ft_strequ("image:", tmp[y]))
			loadimage(tmp + (y + 1));
		else if (ft_strequ("sound:", tmp[y]))
		{
			loadsound(del = ft_strjoin(doom->path, "assets/"),
				tmp + (y + 1), doom);
			free(del);
		}
		else if (ft_strequ("music:", tmp[y]))
		{
			loadmusic(del = ft_strjoin(doom->path, "assets/"),
				tmp + (y + 1), doom);
			free(del);
		}
		else if (ft_strequ("map:", tmp[y]))
		{
			loadmaps(del = ft_strjoin(doom->path, "assets/"), tmp + (y + 1),
				&doom->maps, &doom->mapcount);
			free(del);
		}
		y++;
	}
}
