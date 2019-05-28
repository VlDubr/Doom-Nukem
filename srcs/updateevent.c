/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateevent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:58 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/28 13:13:14 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	checkmousebuttonup(t_doom *doom, SDL_MouseButtonEvent e)
{
	if (e.button == SDL_BUTTON_LEFT)
		doom->setting.input.mousekey[0] = 0;
	if (e.button == SDL_BUTTON_RIGHT)
		doom->setting.input.mousekey[1] = 0;
	if (e.button == SDL_BUTTON_MIDDLE)
		doom->setting.input.mousekey[2] = 0;
}

void	checkmousebuttondown(t_doom *doom, SDL_MouseButtonEvent e)
{
	if (e.button == SDL_BUTTON_LEFT)
		doom->setting.input.mousekey[0] = 1;
	if (e.button == SDL_BUTTON_RIGHT)
		doom->setting.input.mousekey[1] = 1;
	if (e.button == SDL_BUTTON_MIDDLE)
		doom->setting.input.mousekey[2] = 1;
}

void	updateevent(t_doom *doom)
{
	SDL_Keycode key;

	doom->setting.input.mousekey[0] = 0;
	doom->setting.input.mousekey[1] = 0;
	doom->setting.input.mousekey[2] = 0;
	while (SDL_PollEvent(&doom->event))
	{
		doom->event.type == SDL_QUIT ? doom->win->state = 0 : 0;
		doom->setting.input.keystate = SDL_GetKeyboardState(NULL);
		SDL_GetMouseState(&doom->setting.input.mousepos.x,
		&doom->setting.input.mousepos.y);
		if (doom->event.type == SDL_MOUSEBUTTONDOWN)
			checkmousebuttondown(doom, doom->event.button);
		// else if (doom->event.type == SDL_MOUSEBUTTONUP)
		// 	checkmousebuttonup(doom, doom->event.button);
	}
}
