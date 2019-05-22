/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_events.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 17:32:47 by srafe             #+#    #+#             */
/*   Updated: 2019/05/22 17:38:00 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	sec_e(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1 && s->sec_edit < map->sec_count)
		s->sec_edit++;
	else if (s->e.button.button == 3 && s->sec_edit > 0)
		s->sec_edit--;
}

void	floor_e(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1 &&
				(map->sector[s->sec_edit].roof_h
				- map->sector[s->sec_edit].floor_h) > 2)
		map->sector[s->sec_edit].floor_h++;
	else if (s->e.button.button == 3 &&
			map->sector[s->sec_edit].floor_h > 0)
		map->sector[s->sec_edit].floor_h--;
}

void	roof_e(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1)
		map->sector[s->sec_edit].roof_h++;
	else if (s->e.button.button == 3 &&
			map->sector[s->sec_edit].roof_h > 0
			&& (map->sector[s->sec_edit].roof_h -
				map->sector[s->sec_edit].floor_h) > 2)
		map->sector[s->sec_edit].roof_h--;
}

void	r_vis_e(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1)
		map->sector[s->sec_edit].r_visibility = 1;
	else if (s->e.button.button == 3)
		map->sector[s->sec_edit].r_visibility = 0;
}
