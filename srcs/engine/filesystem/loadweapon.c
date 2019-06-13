/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadweapon.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:48:16 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/13 18:04:15 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	loadimageweapon(char *str, t_weapon *weapon)
{
	char **tmp2;

	if (ft_strnequ(str, "image: ", 6))
	{
		tmp2 = ft_strsplit(str, ' ');
		if (stringcount(tmp2) != 2)
			error("Error");
		(*weapon).imageid = ft_atoi(tmp2[1]);
		free2dstring(tmp2);
	}
}

void	loadmaxammo(char *str, t_weapon *weapon)
{
	char **tmp2;

	if (ft_strnequ(str, "maxammo: ", 6))
	{
		tmp2 = ft_strsplit(str, ' ');
		if (stringcount(tmp2) != 2)
			error("Error");
		(*weapon).maxammo = ft_atoi(tmp2[1]);
		free2dstring(tmp2);
	}
}

void	loaddamagetype(char *str, t_weapon *weapon)
{
	char **tmp2;

	if (ft_strnequ(str, "damagetype: ", 6))
	{
		tmp2 = ft_strsplit(str, ' ');
		if (stringcount(tmp2) != 2)
			error("Error");
		(*weapon).dt = ft_atoi(tmp2[1]);
		free2dstring(tmp2);
	}
}

void	loadweapon(char *path, t_weapon **weapon, int y)
{
	char *file;
	char **str;
	char **tmp2;

	file = readfile(path);
	str = ft_strsplit(file, '\n');
	loadnameweapon(str[0], &(*weapon)[y]);
	loadimagetype(str[1], &(*weapon)[y]);
	loadimageweapon(str[2], &(*weapon)[y]);
	loadmaxammo(str[3], &(*weapon)[y]);
	loaddamagetype(str[4], &(*weapon)[y]);
	if (ft_strnequ(str[6], "damage: ", 6))
	{
		tmp2 = ft_strsplit(str[6], ' ');
		if (stringcount(tmp2) != 2)
			error("Error");
		(*weapon)[y].damage = ft_atoi(tmp2[1]);
		free2dstring(tmp2);
	}
	ft_strdel(&path);
	free2dstring(str);
	ft_strdel(&file);
}

void	loadweapons(char *path, char **tmp, t_weapon **weapon, size_t *count)
{
	int	y;
	int	len;

	len = 0;
	y = 0;
	while (tmp[len] != NULL && !ft_strequ("image:", tmp[len])
	&& !ft_strequ("sound:", tmp[len]) && !ft_strequ("maps:", tmp[len]))
		len++;
	(*count) = len;
	(*weapon) = (t_weapon*)malloc(sizeof(t_weapon) * (*count));
	while (y < len)
	{
		loadweapon(ft_strjoin(path, tmp[y]), weapon, y);
		y++;
	}
	ft_strdel(&path);
}
