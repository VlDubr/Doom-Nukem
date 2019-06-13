/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:12:16 by srafe             #+#    #+#             */
/*   Updated: 2019/06/13 13:44:49 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/editor.h"

void	del_obj(t_map *map, t_serv *s)
{
	t_obj	*obj;
	int		i;
	int		j;

	if (map->obj_count > 0)
	{
		obj = (t_obj *)malloc(sizeof(map->obj_count - 1));
		i = -1;
		j = -1;
		while (++i < map->obj_count)
		{
			if (++j == s->obj_edit)
				j++;
			if (j == map->obj_count)
			{
				free(map->obj);
				map->obj = obj;
				map->obj_count--;
				if (s->obj_edit >= map->obj_count && s->obj_edit > 0)
					s->obj_edit--;
				break ;
			}
			obj[i] = map->obj[j];
		}
	}
}
