/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 12:39:20 by srafe             #+#    #+#             */
/*   Updated: 2019/06/05 15:34:40 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	fl_texture(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1)
		map->sector[s->sec_edit].floor_tex++;
	else if (s->e.button.button == 3 &&
			map->sector[s->sec_edit].floor_tex > 0)
		map->sector[s->sec_edit].floor_tex--;
}

void	roof_texture(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1)
		map->sector[s->sec_edit].roof_tex++;
	else if (s->e.button.button == 3 &&
			map->sector[s->sec_edit].roof_tex > 0)
		map->sector[s->sec_edit].roof_tex--;
}

void	sec_tex(t_serv *s, t_map *map)
{
	if (s->e.button.button == 1)
		map->sector[s->sec_edit].texture++;
	else if (s->e.button.button == 3 &&
			map->sector[s->sec_edit].texture > 0)
		map->sector[s->sec_edit].texture--;
}
