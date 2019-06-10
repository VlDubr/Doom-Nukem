/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_units.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:56:55 by srafe             #+#    #+#             */
/*   Updated: 2019/06/10 17:54:17 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/editor.h"

char	*save_w(t_map *map, int i, char *str_old)
{
	char *str;

	str = ft_strjoin(str_old, "w: ");
	str = save_elem(str, map->walls[i].xy[0], ",");
	str = save_elem(str, map->walls[i].xy[1], ",");
	str = save_elem(str, map->walls[i].next_sec, "\n");
	return (str);
}

char	*save_s(t_map *map, int i, char *str_old)
{
	char *str;

	str = ft_strjoin(str_old, "s: ");
	ft_strdel(&str_old);
	str = save_elem(str, map->sector[i].start_pos, " ");
	str = save_elem(str, map->sector[i].w_count, " ");
	str = save_elem(str, map->sector[i].floor_h, " ");
	str = save_elem(str, roof_c(i, map), " ");
	str = save_elem(str, map->sector[i].sec_type, " ");
	str = save_elem(str, map->sector[i].texture, " ");
	str = save_elem(str, map->sector[i].floor_tex, " ");
	str = save_elem(str, map->sector[i].roof_tex, "\n");
	return (str);
}

char	*save_p(t_map *map, char *str_old)
{
	char *str;

	str = ft_strjoin(str_old, "p: ");
	ft_strdel(&str_old);
	str = save_elem(str, map->player.coords[0], ",");
	str = save_elem(str, map->player.coords[1], " ");
	str = save_elem(str, map->player.cam[0], ",");
	str = save_elem(str, map->player.cam[1], ",");
	str = save_elem(str, map->player.cam[2], "\n");
	return (str);
}

char	*save_obj(t_map *map, int i, char *str_old)
{
	char *str;

	str = ft_strjoin(str_old, "o: ");
	ft_strdel(&str_old);
	str = save_elem(str, map->obj[i].type, " ");
	str = save_elem_fl(str, map->obj[i].pos[0], ",");
	str = save_elem_fl(str, map->obj[i].pos[1], ",");
	str = save_elem_fl(str, map->obj[i].pos[2], " ");
	str = save_elem_fl(str, map->obj[i].rot[0], ",");
	str = save_elem_fl(str, map->obj[i].rot[1], ",");
	str = save_elem_fl(str, map->obj[i].rot[2], " ");
	str = save_elem(str, map->obj[i].width, " ");
	str = save_elem(str, map->obj[i].height, " ");
	str = save_elem(str, map->obj[i].health, " ");
	str = save_elem(str, map->obj[i].is_mov, " ");
	str = save_elem_fl(str, map->obj[i].move_s, " ");
	str = save_elem(str, map->obj[i].agr_area, " ");
	str = save_elem(str, map->obj[i].texture, " ");
	str = save_elem(str, map->obj[i].damage, "\n");
	return (str);
}
