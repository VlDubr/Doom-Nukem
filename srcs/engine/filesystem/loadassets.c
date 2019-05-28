/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:39:23 by srafe             #+#    #+#             */
/*   Updated: 2019/05/28 10:39:41 by gdaniel          ###   ########.fr       */
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

void	loadsound(char **tmp)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]))
		y++;
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
			loadsound(tmp + (y + 1));
		else if (ft_strequ("map:", tmp[y]))
			loadmaps(ft_strjoin(doom->path, "assets/"), tmp + (y + 1),
			&doom->maps, &doom->mapcount);
		y++;
	}
	free2dstring(tmp);
	ft_strdel(&path);
}
