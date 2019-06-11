/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menuscene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:54:06 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/11 18:36:45 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	cleartexture(t_window *win)
{
	t_ivector2d cord;

	cord.y = 0;
	while (cord.y < win->size.y)
	{
		cord.x = 0;
		while (cord.x < win->size.x)
		{
			win->pixels[cord.x + (cord.y * win->size.x)] = 0;
			cord.x++;
		}
		cord.y++;
	}
}

static int	boxcollision(t_button button, t_ivector2d mousepos)
{
	if (mousepos.x > button.rect.start.x &&
	mousepos.y > button.rect.start.y &&
	mousepos.x < button.rect.start.x + button.rect.width &&
	mousepos.y < button.rect.start.y + button.rect.height)
		return (1);
	return (0);
}

void		menuupdate(t_doom *doom)
{
	if (doom->setting.input.mousekey[0])
	{
		if (doom->gamestate == 0)
		{
			if (boxcollision(doom->newgame, doom->setting.input.mousepos))
				doom->gamestate = 2;
			if (boxcollision(doom->quit, doom->setting.input.mousepos))
				doom->win->state = 0;
		}
		else if (doom->gamestate == 2)
		{
			if (boxcollision(doom->easy, doom->setting.input.mousepos))
				doom->player.damagemult = 1;
			else if (boxcollision(doom->middle, doom->setting.input.mousepos))
				doom->player.damagemult = 2;
			else if (boxcollision(doom->hard, doom->setting.input.mousepos))
				doom->player.damagemult = 3;
			doom->gamestate = 1;
		}
	}
}

void		drawbuttos(t_doom *doom)
{
	if (doom->gamestate == 0)
	{
		drawimage(doom, doom->newgame.rect, &doom->newgame.texture);
		drawimage(doom, doom->quit.rect, &doom->quit.texture);
	}
	else if (doom->gamestate == 2)
	{
		drawimage(doom, doom->easy.rect, &doom->easy.texture);
		drawimage(doom, doom->middle.rect, &doom->middle.texture);
		drawimage(doom, doom->hard.rect, &doom->hard.texture);
	}
	else if (doom->gamestate == 3)
	{
		drawimage(doom, setirect(setivector2d(doom->win->size.x / 2 - 100,
		doom->win->size.y / 2 - 50), 200, 100), doom->gameoverlogo);
		drawimage(doom, doom->gameoverbutton.rect, &doom->gameoverbutton.texture);
	}
}

void		menudraw(t_doom *doom)
{
	SDL_RenderClear(doom->win->renderer);
	cleartexture(doom->win);
	drawimage(doom, setirect(setivector2d(0, 0), doom->win->size.x,
	doom->win->size.y), doom->skybox);
	//drawimage(doom, setirect(setivector2d(doom->win->size.x / 2 - 100,
	//doom->win->size.y / 2 - 50), 200, 100), doom->logo);
	drawbuttos(doom);
	SDL_UpdateTexture(doom->win->texture, NULL, doom->win->pixels,
	doom->win->size.x * sizeof(uint32_t));
	SDL_RenderCopy(doom->win->renderer, doom->win->texture, NULL, NULL);
	SDL_RenderPresent(doom->win->renderer);
}

void	menuscene(t_doom *doom)
{
	doom->mouseactive = 1;
	menuupdate(doom);
	menudraw(doom);
}
