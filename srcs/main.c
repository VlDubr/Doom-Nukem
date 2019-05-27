/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/27 18:04:43 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

char	*file_read(t_serv *s, char *file)
{
	char	*buf;
	char	*str;
	int		j;

	s->file = file;
	s->fd = open(file, O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
	buf = (char *)malloc(sizeof(char) * 1000);
	str = malloc(0);

	if (s->fd == -1)
		ft_error("Read file error!");
	while ((j = read(s->fd, buf, 1000)) > 0)
	{
		buf[j] = '\0';
		str = ft_strjoin(str, buf);
	}
	return (str);
}

void	writer(t_serv *s, t_sdl sdl, t_map *map)
{
	SDL_RenderClear(sdl.r);
	background(&sdl);
	gui(s, &sdl, map);
	map_writer(&sdl, s, map);
	if (s->p_flag == 1)
		img_write(sdl.r, s->player, s->pl_c);
	SDL_RenderPresent(sdl.r);
}

char	*init(t_map *map, t_serv *s, char *file)
{
	map->sec_count = 0;
	map->wall_count = 0;
	map->player.coords[0] = 0;
	map->player.coords[1] = 0;
	map->player.cam[0] = 0;
	map->player.cam[1] = 0;
	map->player.cam[2] = 0;
	s->w_c = 0;
	s->s_c = 0;
	s->parse_flag = 0;
	s->coord_x = 0;
	s->coord_y = 0;
	s->wh_screen[0] = 1000;
	s->wh_screen[1] = 1000;
	s->sec_edit = 0;
	s->text_wh.x = 28;
	s->text_wh.y = 36;
	s->text = bitmap("assets/img/charmap4.tga", s->text_wh);
	s->player = tga_reader("assets/img/man.tga");
	s->pl_c.x = 0;
	s->pl_c.y = 0;
	s->p_flag = 0;
	s->p_add = 0;
	s->text_c.x = 980;
	s->text_c.y = 10;
	return (file_read(s, file));
}

int		main(int argc, char **argv)
{
	t_sdl		sdl;
	t_serv		*s;
	char		*str;
	t_map		*map;

	if (argc == 2)
	{
		if (!(map = (t_map *)malloc(sizeof(t_map))))
			ft_error("Malloc error!");
		if (!(s = (t_serv *)malloc(sizeof(t_serv))))
			ft_error("Malloc error!");
		str = init(map, s, argv[1]);
		if (ft_strlen(str) >= 39)
			map_parser(s, str, map);
		SDL_Init(SDL_INIT_VIDEO);
		sdl.win = SDL_CreateWindow("DOOM-Nukem Map Editor", 0, 0,
			s->wh_screen[0] + 400, s->wh_screen[1], 0);
		sdl.r = SDL_CreateRenderer(sdl.win, -1, 0);
		writer(s, sdl, map);
		event(s, sdl, map);
	}
	else
		ft_error("Need file path!");
	return (0);
}
