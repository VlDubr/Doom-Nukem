/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:58:57 by srafe             #+#    #+#             */
/*   Updated: 2019/06/14 13:12:18 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

char		*type_obj(int x)
{
	char *str;

	if (x == 0)
		str = ft_strjoin(str, "Decore");
	else if (x == 1)
		str = ft_strjoin(str, "Enemy");
	else if (x == 2)
		str = ft_strjoin(str, "Usable");
	else if (x == 3)
		str = ft_strjoin(str, "L button");
	else if (x == 4)
		str = ft_strjoin(str, "D button");
	else
		str = ft_strjoin(str, "Unknown");
	return (str);
}

static void	obj_buttons3(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	temp = ft_ftoa(map->obj[s->obj_edit].move_s, 2);
	str_wr(s, sdl, "Move speed:", temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].damage);
	str_wr(s, sdl, "Damage:", temp);
	s->text_c.y += 110;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "  RETURN TO MAIN", "");
	s->text_c.y -= 890;
}

static void	obj_buttons2(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	str_wr(s, sdl, "Tex_up:", "");
	s->text_c.y += 60;
	str_wr(s, sdl, "Tex_down:", "");
	s->text_c.y += 60;
	str_wr(s, sdl, "Tex_left:", "");
	s->text_c.y += 60;
	str_wr(s, sdl, "Tex_right:", "");
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].width);
	str_wr(s, sdl, "Width:", temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].height);
	str_wr(s, sdl, "Height:", temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].agr_area);
	str_wr(s, sdl, "Agr area:", temp);
	s->text_c.y += 60;
	temp = ft_itoa(map->obj[s->obj_edit].is_mov);
	str_wr(s, sdl, "Is movable:", temp);
	s->text_c.y += 60;
}

void		no_obj_buttons(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	temp = ft_itoa(s->obj_edit);
	str_wr(s, sdl, "Object :", temp);
	s->text_c.y += 60;
	if (s->obj_edit == map->obj_count)
		bitmap_write(sdl->r, s->text, s->text_c, "Add object");
	else if (s->gui_flag == 1 && s->obj_add == 1)
		bitmap_write(sdl->r, s->text, s->text_c, "Tap to map");
	else
		bitmap_write(sdl->r, s->text, s->text_c, "Del object");
	s->text_c.y += 830;
	temp = ret_str(4, map, s->sec_edit);
	str_wr(s, sdl, "  RETURN TO MAIN", "");
	s->text_c.y -= 890;
}

char	*rotation(t_serv *s, t_map *map, char *str)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	*del;

	temp = ft_itoa(map->obj[s->obj_edit].rot[0]);
	temp2 = ft_itoa(map->obj[s->obj_edit].rot[1]);
	temp3 = ft_itoa(map->obj[s->obj_edit].rot[2]);
	if (map->obj[s->obj_edit].rot[0] > 99)
		str = ft_strjoin(temp, " ");
	else if (map->obj[s->obj_edit].rot[0] > 9)
		str = ft_strjoin(temp, "  ");
	else
		str = ft_strjoin(temp, "   ");
	del = str;
	str = ft_strjoin(str, temp2);
	ft_strdel(&del);
	del = str;
	if (map->obj[s->obj_edit].rot[1] > 99)
		str = ft_strjoin(str, " ");
	else if (map->obj[s->obj_edit].rot[1] > 9)
		str = ft_strjoin(str, "  ");
	else
		str = ft_strjoin(str, "   ");
	ft_strdel(&del);
	del = str;
	str = ft_strjoin(str, temp3);
	ft_strdel(&del);
	ft_strdel(&temp);
	ft_strdel(&temp2);
	ft_strdel(&temp3);
	return (str);
}

void		obj_buttons(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	if (map->obj_count == 0 || s->obj_edit == map->obj_count)
	{
		no_obj_buttons(s, sdl, map);
		return ;
	}
	temp = ft_itoa(s->obj_edit);
	str_wr(s, sdl, "Object :", temp);
	s->text_c.y += 60;
	if (s->gui_flag == 1 && s->obj_add == 1)
		bitmap_write(sdl->r, s->text, s->text_c, "Tap to map");
	else
		bitmap_write(sdl->r, s->text, s->text_c, "Del object");
	s->text_c.y += 60;
	temp = rotation(s, map, temp);
	str_wr(s, sdl, "Rotation:", temp);
	s->text_c.y += 60;
	temp = type_obj(map->obj[s->obj_edit].type_obj);
	str_wr(s, sdl, "Type:", temp);
	s->text_c.y += 60;
	obj_buttons2(s, sdl, map);
	obj_buttons3(s, sdl, map);
}
