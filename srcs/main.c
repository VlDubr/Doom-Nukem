/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:26:53 by srafe             #+#    #+#             */
/*   Updated: 2019/05/18 18:16:17 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

char	*file_read(int fd)
{
	char	*buf;
	char	*str;
	int		j;

	buf = (char *)malloc(sizeof(char) * 1000);
	str = malloc(0);

	if (fd == -1)
		ft_error("error");
	while ((j = read(fd, buf, 1000)) > 0)
	{
		buf[j] = '\0';
		str = ft_strjoin(str, buf);
	}
	return (str);
}

void	writer(t_service *s, t_sdl sdl, t_map *map)
{
	SDL_RenderClear(sdl.r);
	background(s, &sdl);
	map_writer(&sdl, s, map);
	SDL_RenderPresent(sdl.r);
}

void	event(t_service *s, t_sdl sdl, t_map *map)
{
	while (s->quit == 0)
	{
		while (SDL_PollEvent(&s->e))
		{
			if (s->e.type == SDL_QUIT)
				s->quit = 1;
			if (s->e.type == SDLK_ESCAPE)
				s->quit = 1;
			if (s->e.type == SDL_KEYDOWN)
			{
				if (s->e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					s->quit = 1;
				if (s->e.key.keysym.scancode == SDL_SCANCODE_W)
				{
					s->coord_y -= 25;
					writer(s, sdl, map);
				}
				if (s->e.key.keysym.scancode == SDL_SCANCODE_S)
				{
					s->coord_y += 25;
					writer(s, sdl, map);
				}
				if (s->e.key.keysym.scancode == SDL_SCANCODE_D)
				{
					s->coord_x += 25;
					writer(s, sdl, map);
				}
				if (s->e.key.keysym.scancode == SDL_SCANCODE_A)
				{
					s->coord_x -= 25;
					writer(s, sdl, map);
				}
				if (s->e.key.keysym.scancode == SDL_SCANCODE_RETURN)
				{
					s->fd = open("map1.map", O_TRUNC | O_RDWR);
					save_map(map, s);
					close(s->fd);
				}
			}
			if (s->e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (s->e.button.button == 1)
				{
					add_wall_to_map(map, s);
					writer(s, sdl, map);
				}
				if (s->e.button.button == 3 || s->e.button.button == 2)
				{
					delete_wall(map, s);
					writer(s, sdl, map);
				}
			}
		}
	}
}

void	init(t_map *map, t_service *s)
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
}

int		main(int argc, char **argv)
{
	t_sdl		sdl;
	char		*str;
	t_service	*s;
	t_map		*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		ft_error("Malloc error!");
	if (!(s = (t_service *)malloc(sizeof(t_service))))
		ft_error("Malloc error!");
	init(map, s);
	s->fd = open("map.map", O_CREAT | O_RDWR, S_IWRITE | S_IREAD);
	str = file_read(s->fd);
	if (ft_strlen(str) >= 39)
		map_parser(s, str, map);
	SDL_Init(SDL_INIT_VIDEO);
	sdl.win = SDL_CreateWindow("TGA Reader", 0, 0, s->wh_screen[0], s->wh_screen[1], 0);
	sdl.r = SDL_CreateRenderer(sdl.win, -1, 0);
	SDL_RenderClear(sdl.r);
	background(s, &sdl);
	if (s->parse_flag == 1)
		map_writer(&sdl, s, map);
	SDL_RenderPresent(sdl.r);
	SDL_RenderClear(sdl.r);
	event(s, sdl, map);
	return (0);
}