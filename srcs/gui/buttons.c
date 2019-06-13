/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:09:04 by srafe             #+#    #+#             */
/*   Updated: 2019/06/13 17:55:11 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

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
		return (ft_itoa(map->sector[sec_edit].roof_tex));
	return (0);
}

void		str_wr(t_serv *s, t_sdl *sdl, char *str, char *temp2)
{
	char	*temp;

	temp = ft_strjoin(str, temp2);
	bitmap_write(sdl->r, s->text, s->text_c, temp);
	ft_strdel(&temp);
	if (ft_strlen(temp2) != 0)
		ft_strdel(&temp2);
}

static void	next_buttons(t_serv *s, t_sdl *sdl, t_map *map, char *temp)
{
	s->text_c.y += 60;
	temp = ret_str(2, map, s->sec_edit);
	str_wr(s, sdl, "  roof vis:", temp);
	s->text_c.y += 60;
	temp = ret_str(3, map, s->sec_edit);
	str_wr(s, sdl, "  roof tex:", "");
}

static void	first_buttons(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	temp = ft_itoa(s->sec_edit);
	str_wr(s, sdl, "  sector:", temp);
	s->text_c.y += 60;
	str_wr(s, sdl, "  sec tex:", "");
	s->text_c.y += 60;
	temp = ret_str(0, map, s->sec_edit);
	str_wr(s, sdl, "  floor h:", temp);
	s->text_c.y += 60;
	str_wr(s, sdl, "  floor tex", "");
	s->text_c.y += 60;
	temp = ret_str(1, map, s->sec_edit);
	str_wr(s, sdl, "  roof h:", temp);
	next_buttons(s, sdl, map, temp);
}

void		buttons(t_serv *s, t_sdl *sdl, t_map *map)
{
	first_buttons(s, sdl, map);
	s->text_c.y += 60;
	if (s->p_flag == 1)
		bitmap_write(sdl->r, s->text, s->text_c, "  Delete player");
	else
		bitmap_write(sdl->r, s->text, s->text_c, "  Add player");
	s->text_c.y += 60;
	bitmap_write(sdl->r, s->text, s->text_c, "  Objects menu");
	s->text_c.y += 245;
	bitmap_write(sdl->r, s->text, s->text_c, "    CLEAR MAP");
	s->text_c.y += 145;
	bitmap_write(sdl->r, s->text, s->text_c, "    SAVE MAP");
	s->text_c.y -= 870;
}
