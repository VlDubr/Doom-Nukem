/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/06/14 17:02:31 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	main2(t_serv *s, t_sdl sdl, t_map *map, char *str)
{
	event(s, sdl, map);
	ft_strdel(&str);
	unixcommand(ft_strjoin("rm -rf ", "assets.tar"));
	compress(ft_strjoin(s->prog_path, "assets.tar assets"));
	unixcommand(ft_strjoin("rm -rf ", "assets"));
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
		str = init(map, s, argv);
		if (ft_strlen(str) >= 55)
			map_parser(s, str, map);
		SDL_Init(SDL_INIT_VIDEO);
		sdl.win = SDL_CreateWindow("DOOM-Nukem Map Editor", 0, 0,
			s->wh_screen[0] + 560, s->wh_screen[1], 0);
		sdl.r = SDL_CreateRenderer(sdl.win, -1, 0);
		writer(s, sdl, map);
		main2(s, sdl, map, str);
	}
	else
		ft_error("Need file path!");
	return (0);
}
