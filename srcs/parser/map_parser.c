/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:55:06 by srafe             #+#    #+#             */
/*   Updated: 2019/06/10 15:43:55 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void		counter(t_serv *s, char *str, t_map *map)
{
	s->i = 0;
	while (str[s->i] != '\0')
	{
		if (str[s->i] == 'w')
			map->wall_count++;
		if (str[s->i] == 's')
			map->sec_count++;
		if (str[s->i] == 'o')
			map->obj_count++;
		s->i++;
	}
}

void		map_malloc(t_map *map)
{
	if (!(map->sector = (t_sector *)malloc(sizeof(t_sector) * map->sec_count)))
		ft_error("Sector malloc error!");
	if (!(map->walls = (t_wall *)malloc(sizeof(t_wall) * map->wall_count)))
		ft_error("Walls malloc error!");
	if (!(map->obj = (t_obj *)malloc(sizeof(t_obj) * map->obj_count)))
		ft_error("Objects malloc error!");
}

void		map_parser(t_serv *s, char *str, t_map *map)
{
	counter(s, str, map);
	map_malloc(map);
	s->i = 0;
	while (str[s->i] != '\0')
	{
		if (str[s->i] > 96 && str[s->i] < 123 &&
			str[s->i + 1] == ':' && str[s->i - 1] != '#')
		{
			if (str[s->i] == 'w' && s->w_c < map->wall_count)
				s->i = wall_p(map, str, s->i + 3, s->w_c++);
			else if (str[s->i] == 's' && s->s_c < map->sec_count)
				s->i = sec_p(map, str, s->i + 3, s->s_c++);
			else if (str[s->i] == 'p')
				s->i = pl_p(map, str, s->i + 3);
			else if (str[s->i] == 'o' && s->o_c < map->obj_count)
				s->i = obj_p(map, str, s->i + 3, s->o_c++);
		}
		else
			s->i++;
	}
	pl_coords_init(map, s);
	s->parse_flag = 1;
	wall_sector_wr(map);
	close(s->fd);
}
