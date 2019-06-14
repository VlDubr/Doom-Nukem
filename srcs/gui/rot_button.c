/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:20:43 by srafe             #+#    #+#             */
/*   Updated: 2019/06/14 16:23:09 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

char	*rot_return(t_serv *s, t_map *map, char *temp, int num)
{
	char *str;

	if (num > 99)
		str = ft_strjoin(temp, " ");
	else if (num > 9)
		str = ft_strjoin(temp, "  ");
	else
		str = ft_strjoin(temp, "   ");
	return (str);
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
	str = rot_return(s, map, temp, map->obj[s->obj_edit].rot[0]);
	del = str;
	str = ft_strjoin(str, temp2);
	ft_strdel(&del);
	del = str;
	str = rot_return(s, map, str, map->obj[s->obj_edit].rot[1]);
	ft_strdel(&del);
	del = str;
	str = ft_strjoin(str, temp3);
	ft_strdel(&del);
	ft_strdel(&temp);
	ft_strdel(&temp2);
	ft_strdel(&temp3);
	return (str);
}
