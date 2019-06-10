/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:58:57 by srafe             #+#    #+#             */
/*   Updated: 2019/06/10 18:19:29 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

void	obj_buttons(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	temp = ft_itoa(s->sec_edit);
	str_wr(s, sdl, "object :", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(5, map, s->sec_edit);
	str_wr(s, sdl, "obj type:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(5, map, s->sec_edit);
	str_wr(s, sdl, "texture 1:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(0, map, s->sec_edit);
	str_wr(s, sdl, "texture 2:", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(3, map, s->sec_edit);
	str_wr(s, sdl, "texture 3:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(1, map, s->sec_edit);
	str_wr(s, sdl, "texture 4:", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(2, map, s->sec_edit);
	str_wr(s, sdl, "width:", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "height:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "agr area:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "is movable:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "move speed:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "damage:", "");
	ft_strdel(&temp);

	s->text_c.x += 40;
	s->text_c.y += 60;
	if (s->p_flag == 1)
		bitmap_write(sdl->r, s->text, s->text_c, "Del object");
	else
		bitmap_write(sdl->r, s->text, s->text_c, "Add object");
	s->text_c.y += 60;
	s->text_c.x -= 85;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "return to main", "");
	ft_strdel(&temp);
	s->text_c.x += 45;
	s->text_c.y -= 780;
}
