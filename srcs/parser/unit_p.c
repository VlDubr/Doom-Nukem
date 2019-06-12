/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:32:14 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 13:15:03 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

int	wall_p(t_map *map, char *str, int i, int w_c)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * 10);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->walls[w_c].xy[0] = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->walls[w_c].xy[1] = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->walls[w_c].next_sec = ft_atoi(temp);
	ft_strdel(&temp);
	return (i);
}

int	sec_p(t_map *map, char *str, int i, int s_c)
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
	map->sector[s_c].roof_h = roof_vis(map, temp, s_c);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].sec_type = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].texture = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].floor_tex = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->sector[s_c].roof_tex = ft_atoi(temp);
	ft_strdel(&temp);
	return (i);
}

int	pl_p(t_map *map, char *str, int i)
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
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->player.cam[2] = ft_atoi(temp);
	ft_strdel(&temp);
	return (i);
}

int	obj_p_part2(t_map *map, char *str, int i, int o_c)
{
	char	*temp;

	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].height = ft_atoi(temp);
	temp = (char *)malloc(sizeof(char) * 100);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].health = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].is_mov = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].move_s = ft_atof(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].agr_area = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].texture_up = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].texture_down = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].texture_left = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].texture_right = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\01");
	map->obj[o_c].damage = ft_atoi(temp);
	ft_strdel(&temp);
	return (i);
}

int	obj_p(t_map *map, char *str, int i, int o_c)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * 100);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].type_obj = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].type_use = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].is_collide = ft_atoi(temp);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->obj[o_c].pos[0] = ft_atof(temp);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->obj[o_c].pos[1] = ft_atof(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].pos[2] = ft_atof(temp);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->obj[o_c].rot[0] = ft_atof(temp);
	i = ft_str_chr_cpy(temp, str, i, ",\n\00");
	map->obj[o_c].rot[0] = ft_atof(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].rot[2] = ft_atof(temp);
	i = ft_str_chr_cpy(temp, str, i, " \n\00");
	map->obj[o_c].width = ft_atoi(temp);
	ft_strdel(&temp);
	return (obj_p_part2(map, str, i, o_c));
}
