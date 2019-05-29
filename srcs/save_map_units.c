/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_units.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:56:55 by srafe             #+#    #+#             */
/*   Updated: 2019/05/29 18:09:29 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

char	*save_unit(int i, char *delim)
{
	char *str;
	char *del;

	str = ft_itoa(i);
	del = str;
	str = ft_strjoin(str, delim);
	free(del);
	return (str);
}

char	*save_w(t_map *map, int i, char *str_old)
{
	char *del;
	char *str;

	str = ft_strjoin(str_old, "w: ");
	del = str;
	str = ft_strjoin(str, save_unit(map->walls[i].xy[0], ","));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->walls[i].xy[1], ","));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->walls[i].next_sec, "\n"));
	free(del);
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
	str = ft_strjoin(str, save_unit(map->sector[i].start_pos, " "));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->sector[i].w_count, " "));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->sector[i].floor_h, " "));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(roof_c(i, map), " "));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->sector[i].sec_type, " "));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->sector[i].texture, "\n"));
	free(del);
	return (str);
}

char	*save_p(t_map *map, int i, char *str_old)
{
	char *del;
	char *str;

	str = ft_strjoin(str_old, "p: ");
	del = str;
	str = ft_strjoin(str, save_unit(map->player.coords[0], ","));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->player.coords[1], " "));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->player.cam[0], ","));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->player.cam[1], ","));
	free(del);
	del = str;
	str = ft_strjoin(str, save_unit(map->player.cam[2], "\n"));
	free(del);
	return (str);
}
