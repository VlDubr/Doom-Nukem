/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:28:48 by srafe             #+#    #+#             */
/*   Updated: 2019/06/04 17:36:54 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

void		dot_write(t_serv *s, t_sdl *sdl, t_map *map)
{
	int i;
	int x;
	int y;

	i = 0;
	SDL_SetRenderDrawColor(sdl->r, 0, 200, 0, 255);
	while (i < map->wall_count)
	{
		x = map->walls[i].xy[0] + (s->wh_screen[0] / 2) + s->coord_x;
		y = map->walls[i].xy[1] + (s->wh_screen[1] / 2) + s->coord_y;
		SDL_RenderDrawPoint(sdl->r, x + 1, y);
		SDL_RenderDrawPoint(sdl->r, x, y + 1);
		SDL_RenderDrawPoint(sdl->r, x - 1, y);
		SDL_RenderDrawPoint(sdl->r, x, y - 1);
		SDL_RenderDrawPoint(sdl->r, x, y);
		i++;
	}
}

void		background(t_sdl *sdl)
{
	int	y;
	int	x;

	y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			if (x % 25 == 0 && y % 25 == 0)
				SDL_SetRenderDrawColor(sdl->r, 230, 184, 255, 255);
			else
				SDL_SetRenderDrawColor(sdl->r, 0, 0, 0, 255);
			SDL_RenderDrawPoint(sdl->r, x, y);
			x++;
		}
		y++;
	}
}

static void	line_put(double xy[5], t_sdl *sdl)
{
	int i;

	i = 0;
	while (i++ <= xy[4] - 2)
	{
		xy[0] += xy[2];
		xy[1] += xy[3];
		if ((xy[0] > 1100 || xy[1] > 1100) || (xy[0] < -800 || xy[1] < -800))
			return ;
		SDL_RenderDrawPoint(sdl->r, roundf(xy[0]), roundf(xy[1]));
	}
}

void		line_dda(t_wall start, t_wall finish, t_sdl *sdl, t_serv *s)
{
	int		rc[4];
	double	xy[5];

	rc[0] = roundf(start.xy[0]);
	rc[1] = roundf(start.xy[1]);
	rc[2] = roundf(finish.xy[0]);
	rc[3] = roundf(finish.xy[1]);
	xy[4] = ft_max(abs(rc[0] - rc[2]), abs(rc[1] - rc[3])) + 1;
	if (xy[4] == 1)
	{
		SDL_RenderDrawPoint(sdl->r, start.xy[0], start.xy[1]);
		return ;
	}
	xy[2] = (finish.xy[0] - start.xy[0]) / (xy[4] - 1);
	xy[3] = (finish.xy[1] - start.xy[1]) / (xy[4] - 1);
	xy[0] = start.xy[0] + (s->wh_screen[0] / 2) + s->coord_x;
	xy[1] = start.xy[1] + (s->wh_screen[1] / 2) + s->coord_y;
	line_put(xy, sdl);
}

int			wall_comparing(t_sector *sector, t_wall *walls, int w_c, int i)
{
	int prev;

	prev = sector[walls[w_c].sector].start_pos;
	if (walls[i].next_sec != -1
	&& ((walls[i].xy[0] == walls[w_c + 1].xy[0]
	&& walls[i].xy[1] == walls[w_c + 1].xy[1])
	||
	(walls[i].xy[0] == walls[prev].xy[0]
	&& walls[i].xy[1] == walls[prev].xy[1])))
		return (1);
	return (0);
}

int			search_sec(t_sector *sector, t_wall *walls, int w_c)
{
	int sec;
	int i;

	sec = walls[w_c].next_sec;
	i = sector[sec].start_pos;
	if (i > w_c)
	{
		while (i < (sector[sec].w_count + sector[sec].start_pos))
		{
			if (wall_comparing(sector, walls, w_c, i) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}

void		color_ch(t_sdl *sdl, t_serv *s, t_map *map)
{
	if (s->s_c == s->sec_edit)
		SDL_SetRenderDrawColor(sdl->r, 255, 255, 255, 255);
	else
		SDL_SetRenderDrawColor(sdl->r, 128, 0, 0, 255);
	if (map->walls[s->w_c].next_sec != -1
		&& search_sec(map->sector, map->walls, s->w_c) == 1)
		SDL_SetRenderDrawColor(sdl->r, 0, 128, 128, 255);
}

void		map_writer(t_sdl *sdl, t_serv *s, t_map *map)
{
	s->s_c = map->sec_count - 1;
	while (s->s_c >= 0)
	{
		s->w_c = map->sector[s->s_c].start_pos;
		while (s->w_c < map->sector[s->s_c].w_count +
						map->sector[s->s_c].start_pos)
		{
			color_ch(sdl, s, map);
			if (s->w_c + 1 >= map->sector[s->s_c].w_count
							+ map->sector[s->s_c].start_pos)
				line_dda(map->walls[s->w_c],
						map->walls[map->sector[s->s_c].start_pos], sdl, s);
			else
				line_dda(map->walls[s->w_c], map->walls[s->w_c + 1], sdl, s);
			s->w_c++;
		}
		s->s_c--;
	}
}
