/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_units.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:03:29 by srafe             #+#    #+#             */
/*   Updated: 2019/06/10 17:30:40 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/editor.h"

char	*save_unit(int i, char *delim)
{
	char *str;
	char *del;

	str = ft_itoa(i);
	del = str;
	str = ft_strjoin(str, delim);
	ft_strdel(&del);
	return (str);
}

char	*save_elem(char *str, int num, char *c)
{
	char	*str2;
	char	*new;

	str2 = save_unit(num, c);
	new = ft_strjoin(str, str2);
	ft_strdel(&str2);
	ft_strdel(&str);
	return (new);
}

char	*save_unit_fl(float i, char *delim)
{
	char *str;
	char *del;

	str = ft_ftoa(i);
	del = str;
	str = ft_strjoin(str, delim);
	ft_strdel(&del);
	return (str);
}

char	*save_elem_fl(char *str, float num, char *c)
{
	char	*str2;
	char	*new;

	str2 = save_unit_fl(num, c);
	new = ft_strjoin(str, str2);
	ft_strdel(&str2);
	ft_strdel(&str);
	return (new);
}

int		roof_c(int i, t_map *map)
{
	if (map->sector[i].r_visibility == 0)
		return (-map->sector[i].roof_h);
	else
		return (map->sector[i].roof_h);
}
