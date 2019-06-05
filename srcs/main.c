/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/06/05 16:24:02 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

char	*file_read(t_serv *s, char *file)
{
	char	buf[1001];
	char	*str;
	char	*del;
	int		j;

	s->file = file;
	s->fd = open(file, O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
	str = malloc(0);
	if (s->fd == -1)
		ft_error("Read file error!");
	while ((j = read(s->fd, buf, 1000)) > 0)
	{
		del = str;
		buf[j] = '\0';
		str = ft_strjoin(str, buf);
		ft_strdel(&del);
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
		pl_write(s, sdl);
	dot_write(s, &sdl, map);
	SDL_RenderPresent(sdl.r);
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
		if (ft_strlen(str) >= 55)
			map_parser(s, str, map);
		SDL_Init(SDL_INIT_VIDEO);
		sdl.win = SDL_CreateWindow("DOOM-Nukem Map Editor", 0, 0,
			s->wh_screen[0] + 400, s->wh_screen[1], 0);
		sdl.r = SDL_CreateRenderer(sdl.win, -1, 0);
		writer(s, sdl, map);
		event(s, sdl, map);
		ft_strdel(&str);
	}
	else
		ft_error("Need file path!");
	return (0);
}
