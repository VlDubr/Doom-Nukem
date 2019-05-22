/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/22 13:17:53 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

char	*file_read(t_serv *s)
{
	char	*buf;
	char	*str;
	int		j;

	s->fd = open("map1.map", O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
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
	gui(s, &sdl);
	map_writer(&sdl, s, map);
	SDL_RenderPresent(sdl.r);
}

void	init(t_map *map, t_serv *s)
{
	map->sec_count = 0;
	map->wall_count = 0;
	s->i = 0;
	s->j = 0;
	s->w_c = 0;
	s->s_c = 0;
	s->quit = 0;
	s->fd = 0;
	s->parse_flag = 0;
	s->coord_x = 0;
	s->coord_y = 0;
	s->wh_screen[0] = 1000;
	s->wh_screen[1] = 1000;
	s->sec_edit = 0;
	s->text_wh.x = 7;
	s->text_wh.y = 9;
	s->text = bitmap("assets/img/charmap.tga", s->text_wh);
	s->text_wh.x = 1100;
	s->text_wh.y = 200;
}

int		main(int argc, char **argv)
{
	t_sdl		sdl;
	char		*str;
	t_serv		*s;
	t_map		*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		ft_error("Malloc error!");
	if (!(s = (t_serv *)malloc(sizeof(t_serv))))
		ft_error("Malloc error!");
	init(map, s);
	str = file_read(s);
	if (ft_strlen(str) >= 39)
		map_parser(s, str, map);
	SDL_Init(SDL_INIT_VIDEO);
	sdl.win = SDL_CreateWindow("TGA Reader", 0, 0,
		s->wh_screen[0] + 400, s->wh_screen[1], 0);
	sdl.r = SDL_CreateRenderer(sdl.win, -1, 0);
	background(&sdl);
	gui(s, &sdl);
	if (s->parse_flag == 1)
		map_writer(&sdl, s, map);
	SDL_RenderPresent(sdl.r);
	SDL_RenderClear(sdl.r);
	event(s, sdl, map);
	return (0);
}
