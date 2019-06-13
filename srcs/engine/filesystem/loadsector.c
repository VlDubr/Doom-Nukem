/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadsector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:54:08 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 18:32:25 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initsector(char *str, t_sector **sector, int y2)
{
	char	**tmp;

	tmp = ft_strsplit(str, ' ');
	(*sector)[y2].start = ft_atoi(tmp[1]);
	(*sector)[y2].count = ft_atoi(tmp[2]);
	(*sector)[y2].floor = ft_atoi(tmp[3]);
	(*sector)[y2].height = ft_atoi(tmp[4]);
	(*sector)[y2].type = ft_atoi(tmp[5]);
	(*sector)[y2].walltexture = ft_atoi(tmp[6]);
	(*sector)[y2].floortexture = ft_atoi(tmp[7]);
	(*sector)[y2].light = 0;
	(*sector)[y2].id = y2;
	free2dstring(tmp);
}

void	loadsector(char **str, t_sector **sector, size_t *count)
{
	int		y;
	int		y2;

	y = 0;
	(*count) = 0;
	while (str[y] != NULL)
	{
		if (str[y][0] == 's' && str[y][1] == ':')
			(*count)++;
		y++;
	}
	y = 0;
	y2 = 0;
	*sector = (t_sector*)malloc(sizeof(t_sector) * (*count + 1));
	while (str[y] != NULL)
	{
		if (str[y][0] == 's' && str[y][1] == ':')
		{
			initsector(str[y], sector, y2);
			y2++;
		}
		y++;
	}
}
