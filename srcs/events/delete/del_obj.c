/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:12:16 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 17:27:59 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/editor.h"

void	del_obj(t_map *map, t_serv *s)
{
	t_obj	*obj;
	int		i;

	if (map->obj_count > 0)
	{
		obj = (t_obj *)malloc(sizeof(map->obj_count - 1));
		i = 0;
		while (i < map->obj_count)
		{
			if (i == s->obj_edit)
				i++;
			obj[i] = map->obj[i];
			i++;
		}
		free(map->obj);
		map->obj = obj;
	}
}
