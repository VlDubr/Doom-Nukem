/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:28:48 by srafe             #+#    #+#             */
/*   Updated: 2019/05/21 19:05:35 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

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
				SDL_SetRenderDrawColor(sdl->r, 37, 0, 65, 255);
			SDL_RenderDrawPoint(sdl->r, x, y);
			x++;
		}
		y++;
	}
}

void		gui(t_serv *s, t_sdl *sdl)
{
	int	y;
	int	x;
	char *temp;
	char *temp2;;

	y = 0;
	while (y < 1000)
	{
		x = 1000;
		while (x < 1400)
		{
			if (y < 500)
				SDL_SetRenderDrawColor(sdl->r, 92, 92, 92, 255);
			else
				SDL_SetRenderDrawColor(sdl->r, 123, 2, 43, 255);
			SDL_RenderDrawPoint(sdl->r, x, y);
			x++;
		}
		y++;
	}
	temp2 = ft_itoa(s->sec_edit);
	temp = ft_strjoin("sector: ", temp2);
	bitmap_write(sdl->r, s->text, s->text_wh, temp);
	free(temp);
	free(temp2);
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

void		map_writer(t_sdl *sdl, t_serv *s, t_map *map)
{
	s->s_c = 0;
	while (s->s_c < map->sec_count)
	{
		s->w_c = map->sector[s->s_c].start_pos;
		while (s->w_c < map->sector[s->s_c].w_count +
						map->sector[s->s_c].start_pos)
		{
			if (map->walls[s->w_c].next_sec == -1)
				SDL_SetRenderDrawColor(sdl->r, 255, 255, 255, 255);
			else 
				SDL_SetRenderDrawColor(sdl->r, 255, 0, 0, 255);
			if (s->w_c + 1 >= map->sector[s->s_c].w_count
							+ map->sector[s->s_c].start_pos)
				line_dda(map->walls[s->w_c],
						map->walls[map->sector[s->s_c].start_pos], sdl, s);
			else
				line_dda(map->walls[s->w_c], map->walls[s->w_c + 1], sdl, s);
			s->w_c++;
		}
		s->s_c++;
	}
}
