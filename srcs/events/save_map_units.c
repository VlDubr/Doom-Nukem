/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_units.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:56:55 by srafe             #+#    #+#             */
/*   Updated: 2019/06/06 18:54:43 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

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
	return (new);
}

char	*save_w(t_map *map, int i, char *str_old)
{
	char *del;
	char *str;

	str = ft_strjoin(str_old, "w: ");
	del = str;
	str = save_elem(str, map->walls[i].xy[0], ",");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->walls[i].xy[1], ",");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->walls[i].next_sec, "\n");
	ft_strdel(&del);
	return (str);
}

int		roof_c(int i, t_map *map)
{
	if (map->sector[i].r_visibility == 0)
		return (-map->sector[i].roof_h);
	else
		return (map->sector[i].roof_h);
}

char	*save_s(t_map *map, int i, char *str_old)
{
	char *del;
	char *str;

	str = ft_strjoin(str_old, "s: ");
	del = str;
	str = save_elem(str, map->sector[i].start_pos, " ");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->sector[i].w_count, " ");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->sector[i].floor_h, " ");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, roof_c(i, map), " ");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->sector[i].sec_type, " ");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->sector[i].texture, " ");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->sector[i].floor_tex, " ");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->sector[i].roof_tex, "\n");
	ft_strdel(&del);
	return (str);
}

char	*save_p(t_map *map, char *str_old)
{
	char *del;
	char *str;

	str = ft_strjoin(str_old, "p: ");
	del = str;
	str = save_elem(str, map->player.coords[0], ",");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->player.coords[1], " ");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->player.cam[0], ",");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->player.cam[1], ",");
	ft_strdel(&del);
	del = str;
	str = save_elem(str, map->player.cam[2], "\n");
	ft_strdel(&del);
	return (str);
}
