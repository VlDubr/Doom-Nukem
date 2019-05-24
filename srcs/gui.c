/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srafe <srafe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:58:27 by srafe             #+#    #+#             */
/*   Updated: 2019/05/24 15:37:49 by srafe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/editor.h"

char		*ret_str(int flag, t_map *map, int sec_edit)
{
	if (map->sec_count == sec_edit)
		return (ft_itoa(0));
	else if (flag == 0)
		return (ft_itoa(map->sector[sec_edit].floor_h));
	else if (flag == 1)
		return (ft_itoa(map->sector[sec_edit].roof_h));
	else
		return (ft_itoa(map->sector[sec_edit].r_visibility));
}

void		str_wr(t_serv *s, t_sdl *sdl, char *str, char *temp2)
{
	char	*temp;

	s->text_c.x += 60;
	temp = ft_strjoin(str, temp2);
	bitmap_write(sdl->r, s->text, s->text_c, temp);
	s->text_c.x -= 60;
	free(temp);
}

void		text_wr(t_serv *s, t_sdl *sdl, t_map *map)
{
	char	*temp;

	temp = ft_itoa(s->sec_edit);
	str_wr(s, sdl, "sector :", temp);
	free(temp);
	s->text_c.y += 60;
	temp = ret_str(0, map, s->sec_edit);
	str_wr(s, sdl, "floor h:", temp);
	free(temp);
	s->text_c.y += 60;
	temp = ret_str(1, map, s->sec_edit);
	str_wr(s, sdl, "roof h:", temp);
	free(temp);
	s->text_c.y += 60;
	temp = ret_str(2, map, s->sec_edit);
	str_wr(s, sdl, "roof vis:", temp);
	free(temp);

	s->text_c.y += 690;
	s->text_c.x += 80;
	bitmap_write(sdl->r, s->text, s->text_c, "SAVE MAP");
	s->text_c.x -= 80;

	s->text_c.y -= 870;
}

static void	gui_colors(t_sdl *sdl, int x, int y)
{
	if (y < 60)
		SDL_SetRenderDrawColor(sdl->r, 92, 92, 92, 255);
	else if (y < 120)
		SDL_SetRenderDrawColor(sdl->r, 139, 0, 139, 255);
	else if (y < 180)
		SDL_SetRenderDrawColor(sdl->r, 139, 69, 19, 255);
	else if (y < 240)
		SDL_SetRenderDrawColor(sdl->r, 123, 2, 43, 255);
	else if (y > 800)
		SDL_SetRenderDrawColor(sdl->r, 139, 69, 19, 255);
	else
		SDL_SetRenderDrawColor(sdl->r, 188, 143, 143, 255);
}

void		gui(t_serv *s, t_sdl *sdl, t_map *map)
{
	int		y;
	int		x;

	y = 0;
	while (y < 1000)
	{
		x = 1000;
		while (x < 1400)
		{
			gui_colors(sdl, x, y);
			SDL_RenderDrawPoint(sdl->r, x, y);
			x++;
		}
		y++;
	}
	text_wr(s, sdl, map);
}
