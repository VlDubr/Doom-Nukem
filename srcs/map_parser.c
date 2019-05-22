/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 13:55:06 by srafe             #+#    #+#             */
/*   Updated: 2019/05/22 13:13:58 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

static int	wall_p(t_map *map, char *str, int i, int w_c)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * 10);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->walls[w_c].xy[0] = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->walls[w_c].xy[1] = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->walls[w_c].next_sec = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->walls[w_c].next_type = ft_atoi(temp);

	free(temp);
	return (i);
}

static int	sec_p(t_map *map, char *str, int i, int s_c)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * 10);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].start_pos = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].w_count = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].floor_h = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].roof_h = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].sec_type = ft_atoi(temp);

	free(temp);
	return (i);
}

static int	pl_p(t_map *map, char *str, int i)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * 10);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->player.coords[0] = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->player.coords[1] = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->player.cam[0] = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->player.cam[1] = ft_atoi(temp);

	i = ft_str_chr_cpy(temp, str, i, " \n\01");
	map->player.cam[2] = ft_atoi(temp);

	free(temp);
	return (i);
}

void		counter(t_serv *s, char *str, t_map *map)
{
	while (str[s->i] != '\0')
	{
		if (str[s->i] == 'w')
			map->wall_count++;
		if (str[s->i] == 's')
			map->sec_count++;
		s->i++;
	}
}

void		map_parser(t_serv *s, char *str, t_map *map)
{
	counter(s, str, map);
	if (!(map->sector = (t_sector *)malloc(sizeof(t_sector) * map->sec_count)))
		ft_error("Malloc error!");
	if (!(map->walls = (t_wall *)malloc(sizeof(t_wall) * map->wall_count)))
		ft_error("Malloc error!");
	s->i = 0;
	while (str[s->i] != '\0')
	{
		if (str[s->i] == 'w' && s->w_c < map->wall_count)
			s->i = wall_p(map, str, s->i + 3, s->w_c++);
		else if (str[s->i] == 's' && s->s_c < map->sec_count)
			s->i = sec_p(map, str, s->i + 3, s->s_c++);
		else if (str[s->i] == 'p')
			s->i = pl_p(map, str, s->i + 3);
		else
			s->i++;
	}
	s->parse_flag = 1;
	close(s->fd);
}
