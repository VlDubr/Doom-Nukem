/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:09:04 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 18:19:15 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

char		*ret_str(int flag, t_map *map, int sec_edit)
{
	if (map->sec_count == sec_edit)
		return (ft_itoa(0));
	else if (flag == 0)
		return (ft_itoa(map->sector[sec_edit].floor_h));
	else if (flag == 1)
		return (ft_itoa(map->sector[sec_edit].roof_h));
	else if (flag == 2)
		return (ft_itoa(map->sector[sec_edit].r_visibility));
	else if (flag == 3)
		return (ft_itoa(map->sector[sec_edit].floor_tex));
	else if (flag == 4)
		return (ft_itoa(map->sector[sec_edit].roof_tex));
	else if (flag == 5)
		return (ft_itoa(map->sector[sec_edit].texture));
	return (0);
}

void		str_wr(t_serv *s, t_sdl *sdl, char *str, char *temp2)
{
	char	*temp;

	s->text_c.x += 60;
	temp = ft_strjoin(str, temp2);
	bitmap_write(sdl->r, s->text, s->text_c, temp);
	s->text_c.x -= 60;
	free(temp);
}

static void	next_buttons(t_serv *s, t_sdl *sdl, t_map *map, char *temp)
{
	s->text_c.y += 60;
	temp = ret_str(2, map, s->sec_edit);
	str_wr(s, sdl, "roof vis:", temp);
	free(temp);
	s->text_c.y += 60;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "roof tex:", temp);
	free(temp);
}

static void	first_buttons(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	temp = ft_itoa(s->sec_edit);
	str_wr(s, sdl, "sector :", temp);
	free(temp);
	s->text_c.y += 60;
	temp = ret_str(5, map, s->sec_edit);
	str_wr(s, sdl, "sec tex:", temp);
	free(temp);
	s->text_c.y += 60;
	temp = ret_str(0, map, s->sec_edit);
	str_wr(s, sdl, "floor h:", temp);
	free(temp);
	s->text_c.y += 60;
	temp = ret_str(3, map, s->sec_edit);
	str_wr(s, sdl, "floor tex:", temp);
	free(temp);
	s->text_c.y += 60;
	temp = ret_str(1, map, s->sec_edit);
	str_wr(s, sdl, "roof h:", temp);
	free(temp);
	next_buttons(s, sdl, map, temp);
}

void		text_wr(t_serv *s, t_sdl *sdl, t_map *map)
{
	first_buttons(s, sdl, map);
	s->text_c.x += 60;
	s->text_c.y += 60;
	if (s->p_flag == 1)
		bitmap_write(sdl->r, s->text, s->text_c, "Del player");
	else
		bitmap_write(sdl->r, s->text, s->text_c, "Add player");
	s->text_c.x += 20;
	s->text_c.y += 305;
	bitmap_write(sdl->r, s->text, s->text_c, "CLEAR MAP");
	s->text_c.y += 145;
	bitmap_write(sdl->r, s->text, s->text_c, "SAVE MAP");
	s->text_c.x -= 80;
	s->text_c.y -= 870;
}
