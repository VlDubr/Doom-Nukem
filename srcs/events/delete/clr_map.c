/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:15:15 by srafe             #+#    #+#             */
/*   Updated: 2019/06/14 14:39:23 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/editor.h"

void	clr_map(t_map *map, t_serv *s)
{
	free(map->sector);
	free(map->walls);
	free(map->obj);
	map->sec_count = 0;
	map->wall_count = 0;
	map->obj_count = 0;
	s->p_flag = 0;
	s->p_add = 0;
	s->sec_edit = 0;
}
