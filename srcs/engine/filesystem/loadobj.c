/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadobj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:52:38 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 18:39:38 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initobj2(char **str, t_object **obj, int y)
{
	(*obj)[y].width = ft_atof(str[6]);
	(*obj)[y].height = ft_atoi(str[7]);
	(*obj)[y].maxhealth = ft_atoi(str[8]);
	(*obj)[y].health = (*obj)[y].maxhealth;
	(*obj)[y].ismoveble = ft_atoi(str[9]);
	(*obj)[y].movespeed = ft_atof(str[10]);
	(*obj)[y].agressionarea = ft_atoi(str[11]);
	(*obj)[y].textureup = ft_atoi(str[12]);
	(*obj)[y].texturedown = ft_atoi(str[13]);
	(*obj)[y].textureleft = ft_atoi(str[14]);
	(*obj)[y].texturerigth = ft_atoi(str[15]);
	(*obj)[y].damage = ft_atoi(str[16]);
	(*obj)[y].dscmax = 100;
	(*obj)[y].isactive = 1;
}

void	initobj(char **str, t_object **obj, int y)
{
	char	**tmp2;

	(*obj)[y].typeobject = ft_atoi(str[1]);
	(*obj)[y].typeuse = ft_atoi(str[2]);
	(*obj)[y].iscollide = ft_atoi(str[3]);
	tmp2 = ft_strsplit(str[4], ',');
	(*obj)[y].pos = setfvector(ft_atof(tmp2[0]), ft_atof(tmp2[1]),
	ft_atof(tmp2[2]), 1);
	free2dstring(tmp2);
	tmp2 = ft_strsplit(str[5], ',');
	(*obj)[y].rotate = setfvector(ft_atof(tmp2[0]), ft_atof(tmp2[1]),
	ft_atof(tmp2[2]), 1);
	free2dstring(tmp2);
	initobj2(str, obj, y);
	(*obj)[y].dsc = (*obj)[y].dscmax;
}

void	loadobj(char **str, t_object **obj, size_t *count)
{
	t_ivector2d	cord;
	char		**tmp;

	cord.x = 0;
	(*count) = 0;
	while (str[cord.x] != NULL)
	{
		if (str[cord.x][0] == 'o' && str[cord.x][1] == ':')
			(*count)++;
		cord.x++;
	}
	*obj = (t_object*)malloc(sizeof(t_object) * (*count + 1));
	cord.x = 0;
	cord.y = 0;
	while (str[cord.x] != NULL)
	{
		if (str[cord.x][0] == 'o' && str[cord.x][1] == ':')
		{
			tmp = ft_strsplit(str[cord.x], ' ');
			initobj(tmp, obj, cord.y);
			free2dstring(tmp);
			cord.y++;
		}
		cord.x++;
	}
}
