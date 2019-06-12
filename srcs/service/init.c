/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:59:05 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 12:58:49 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/editor.h"

char		*prog_path(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '/')
		i--;
	new = ft_strdup(str);
	j = 0;
	while (j <= i)
	{
		new[j] = str[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

static void	service_init(t_serv *s)
{
	char *str;

	s->w_c = 0;
	s->s_c = 0;
	s->o_c = 0;
	s->parse_flag = 0;
	s->coord_x = 0;
	s->coord_y = 0;
	s->wh_screen[0] = 1000;
	s->wh_screen[1] = 1000;
	s->sec_edit = 0;
	s->text_wh.x = 28;
	s->text_wh.y = 36;
	str = ft_strjoin(s->prog_path, "assets/image/editor/charmap4.tga");
	s->text = bitmap(str, s->text_wh);
	ft_strdel(&str);
	str = ft_strjoin(s->prog_path, "assets/image/editor/man.tga");
	s->player = tga_reader(str);
	ft_strdel(&str);
	s->pl_c.x = 0;
	s->pl_c.y = 0;
	s->p_flag = 0;
	s->p_add = 0;
	s->text_c.x = 980;
	s->text_c.y = 10;
}

char		*init(t_map *map, t_serv *s, char **argv)
{
	char	*str1;
	char	*str2;

	map->sec_count = 0;
	map->wall_count = 0;
	map->player.coords[0] = 0;
	map->player.coords[1] = 0;
	map->player.cam[0] = 0;
	map->player.cam[1] = 0;
	map->player.cam[2] = 0;
	map->obj_count = 0;
	s->prog_path = prog_path(argv[0]);
	str1 = ft_strjoin(s->prog_path, "assets/assets.cfg");
	str2 = ft_strjoin(s->prog_path, "assets/");
	img_parse(str1, str2, map, s);
	ft_strdel(&str1);
	free(s->prog_path);
	s->prog_path = prog_path(argv[0]);
	s->gui_flag = 0;
	service_init(s);
	s->file = argv[1];
	return (file_read(s->fd, argv[1]));
}
