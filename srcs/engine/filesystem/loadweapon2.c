/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadweapon2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:30:23 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:58:29 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	loadimagetype(char *str, t_weapon *weapon)
{
	char **tmp2;
	char **tmp3;

	if (ft_strnequ(str, "imagetype: ", 11))
	{
		tmp2 = ft_strsplit(str, ' ');
		if (stringcount(tmp2) < 2)
			error("Error");
		(*weapon).imagetype.x = ft_atoi(tmp2[1]);
		if ((*weapon).imagetype.x)
		{
			tmp3 = ft_strsplit(tmp2[2], ',');
			(*weapon).imagetype.y = ft_atoi(tmp3[0]);
			(*weapon).imagetype.z = ft_atoi(tmp3[1]);
			free2dstring(tmp3);
		}
		free2dstring(tmp2);
	}
}

void	loadnameweapon(char *str, t_weapon *weapon)
{
	char **tmp2;

	if (ft_strnequ(str, "name: ", 6))
	{
		tmp2 = ft_strsplit(str, ' ');
		if (stringcount(tmp2) != 2)
			error("Error");
		(*weapon).name = ft_strdup(tmp2[1]);
		free2dstring(tmp2);
	}
}
