/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/06/12 12:52:54 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void	tex_write(t_serv *s, t_sdl sdl, t_map *map)
{
	int xy[2];
	int wh[2];

	if (s->gui_flag == 0)
	{
		xy[0] = 1280;
		xy[1] = 67;
		wh[0] = 45;
		wh[1] = 45;
		drawimage(&sdl, xy, wh,
			&map->textures[map->sector[s->sec_edit].texture]);
		xy[0] = 1325;
		xy[1] = 187;
		drawimage(&sdl, xy, wh,
			&map->textures[map->sector[s->sec_edit].floor_tex]);
		xy[0] = 1325;
		xy[1] = 367;
		drawimage(&sdl, xy, wh,
			&map->textures[map->sector[s->sec_edit].roof_tex]);
	}
	else if (s->gui_flag == 1)
	{
		
	}
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
	if (s->sec_edit < map->sec_count)
		tex_write(s, sdl, map);
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
		str = init(map, s, argv);
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
