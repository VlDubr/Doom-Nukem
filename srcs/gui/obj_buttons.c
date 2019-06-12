/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:58:57 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 18:39:08 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

char		*type_obj(int x)
{
	char *str;

	if (x == 0)
		str = ft_strjoin(str, "decore");
	else if (x == 1)
		str = ft_strjoin(str, "enemy");
	else if (x == 2)
		str = ft_strjoin(str, "usable");
	else if (x == 3)
		str = ft_strjoin(str, "l button");
	else if (x == 4)
		str = ft_strjoin(str, "d button");
	else
		str = ft_strjoin(str, "unknown");
	return (str);
}

static void	obj_buttons3(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].is_mov);
	str_wr(s, sdl, "  is movable:", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].move_s);
	str_wr(s, sdl, "  move speed:", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].damage);
	str_wr(s, sdl, "  damage:", temp);
	ft_strdel(&temp);
	s->text_c.y += 110;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "  RETURN TO MAIN", "");
	ft_strdel(&temp);
	s->text_c.y -= 890;
}

static void	obj_buttons2(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].texture_left);
	str_wr(s, sdl, "  tex_left:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].texture_right);
	str_wr(s, sdl, "  tex_right:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].width);
	str_wr(s, sdl, "  width:", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].height);
	str_wr(s, sdl, "  height:", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].agr_area);
	str_wr(s, sdl, "  agr area:", temp);
	ft_strdel(&temp);
	obj_buttons3(s, sdl, map);
}

void		obj_buttons(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	temp = ft_itoa(s->obj_edit);
	str_wr(s, sdl, "  object :", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	bitmap_write(sdl->r, s->text, s->text_c, "  Add object");
	s->text_c.y += 60;
	bitmap_write(sdl->r, s->text, s->text_c, "  Del object");
	s->text_c.y += 60;
	temp = type_obj(map->obj[s->obj_edit].type_obj);
	str_wr(s, sdl, "  obj type:", temp);
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].texture_up);
	str_wr(s, sdl, "  tex_up:", "");
	ft_strdel(&temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].texture_down);
	str_wr(s, sdl, "  tex_down:", "");
	ft_strdel(&temp);
	obj_buttons2(s, sdl, map);
}
