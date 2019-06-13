/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:12:58 by srafe             #+#    #+#             */
/*   Updated: 2019/06/13 15:55:51 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	loadimages(char *path, char **tmp, t_tga **textures, int *count)
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

void	img_parse(char *assets, char *images, t_map *map, t_serv *s)
{
	char	*cfg;
	char	**temp;
	int		y;
	int		fd;

	cfg = file_read(fd, assets);
	temp = ft_strsplit(cfg, '\n');
	y = 0;
	while (temp[y] != NULL)
	{
		if (ft_strequ("image:", temp[y]))
		{
			loadimages(images, temp + (y + 1),
				&map->textures, &map->tex_count);
			break ;
		}
		y++;
	}
	ft_strdel(&cfg);
	del_str_mass(temp);
	close(fd);
}
