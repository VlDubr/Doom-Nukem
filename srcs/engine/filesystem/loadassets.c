/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadassets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 13:39:23 by srafe             #+#    #+#             */
/*   Updated: 2019/04/24 15:41:55 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	loadimage(char **tmp)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("sound:", tmp[y])
	&& !ft_strequ("map:", tmp[y]))
		y++;
}

t_sound	*loadsound(char *path, char **tmp, t_sound *s)
{
	int		y;

	y = 0;
	while (tmp[y] != NULL && !ft_strequ("image:", tmp[y])
	&& !ft_strequ("map:", tmp[y]))
		y++;
	return (s);
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
			doom->sounds = loadsound(ft_strjoin(doom->path, "assets/"),
			tmp + (y + 1), doom->sounds);
		else if (ft_strequ("map:", tmp[y]))
			loadmaps(ft_strjoin(doom->path, "assets/"), tmp + (y + 1),
			&doom->maps, &doom->mapcount);
		y++;
	}
}
