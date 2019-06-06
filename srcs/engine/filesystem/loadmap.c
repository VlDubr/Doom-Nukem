/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 14:45:18 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/03 19:13:20 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	initwall(char *str, t_fvector *wall)
{
	char		**tmp;
	char		**tmp2;

	tmp = ft_strsplit(str, ' ');
	tmp2 = ft_strsplit(tmp[1], ',');
	(*wall).x = ft_atoi(tmp2[0]);
	(*wall).y = ft_atoi(tmp2[1]);
	(*wall).z = ft_atoi(tmp2[2]);
	(*wall).w = 0;
	free2dstring(tmp);
	free2dstring(tmp2);
}

void	loadwall(char **str, t_fvector **wall, size_t *count)
{
	t_ivector2d	cord;
	char		**tmp;
	char		**tmp2;

	cord.x = 0;
	(*count) = 0;
	while (str[cord.x] != NULL)
	{
		if (str[cord.x][0] == 'w' && str[cord.x][1] == ':')
			(*count)++;
		cord.x++;
	}
	cord.x = 0;
	cord.y = 0;
	*wall = (t_fvector*)malloc(sizeof(t_fvector) * (*count + 1));
	while (str[cord.x] != NULL)
	{
		if (str[cord.x][0] == 'w' && str[cord.x][1] == ':')
		{
			initwall(str[cord.x], &(*wall)[cord.y]);
			cord.y++;
		}
		cord.x++;
	}
}

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
	*sector = (t_sector*)malloc(sizeof(t_sector) * (*count));
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

void	initobj(char **str, t_object **obj, int y)
{
	char	**tmp2;

	(*obj)[y].typeobject = ft_atoi(str[1]);

	tmp2 = ft_strsplit(str[2], ',');
	(*obj)[y].pos = setfvector(ft_atof(tmp2[0]), ft_atof(tmp2[1]),
	ft_atof(tmp2[2]), 1);
	free2dstring(tmp2);
	tmp2 = ft_strsplit(str[3], ',');
	(*obj)[y].rotate = setfvector(ft_atof(tmp2[0]), ft_atof(tmp2[1]),
	ft_atof(tmp2[2]), 1);
	free2dstring(tmp2);
	(*obj)[y].width = ft_atof(str[4]);
	(*obj)[y].maxhealth = ft_atoi(str[5]);
	(*obj)[y].health = (*obj)[y].maxhealth;
	(*obj)[y].ismoveble = ft_atoi(str[6]);
	(*obj)[y].movespeed = ft_atof(str[7]);
	(*obj)[y].agressionarea = ft_atof(str[8]);
	(*obj)[y].texture = ft_atoi(str[9]);
	(*obj)[y].damage = ft_atoi(str[10]);
	(*obj)[y].dscmax = 100;
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
	*obj = (t_object*)malloc(sizeof(t_object) * (*count));
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

void	initplayer(char *str, t_player *player)
{
	char	**tmp;
	char	**tmp2;

	tmp = ft_strsplit(str, ' ');
	tmp2 = ft_strsplit(tmp[1], ',');
	player->pos = setfvector(ft_atof(tmp2[0]), 0, ft_atof(tmp2[1]), 0);
	free2dstring(tmp2);
	tmp2 = ft_strsplit(tmp[2], ',');
	player->rotate = setfvector(ft_atof(tmp2[0]), ft_atof(tmp2[1]),
	ft_atof(tmp2[2]), 0);
	free2dstring(tmp2);
	free2dstring(tmp);
}

void	loadplayer(char **str, t_player *player)
{
	int		y;
	int		flag;
	char	**tmp;
	char	**tmp2;

	y = 0;
	flag = 0;
	while (str[y] != NULL)
	{
		if (str[y][0] == 'p' && str[y][1] == ':')
		{
			if (!flag)
				flag = 1;
			else
				error("Error: player");
			initplayer(str[y], player);
		}
		y++;
	}
}

t_map	loadmap(char *path)
{
	t_map	r;
	char	*str;
	char	**tmp;

	str = readfile(path);
	tmp = ft_strsplit(str, '\n');
	loadwall(tmp, &r.walls, &r.wallcount);
	loadsector(tmp, &r.sectors, &r.sectorcount);
	loadplayer(tmp, &r.startplayer);
	loadobj(tmp, &r.obj, &r.objcount);
	free2dstring(tmp);
	ft_strdel(&str);
	return (r);
}
