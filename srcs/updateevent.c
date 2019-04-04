/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateevent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:58 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 16:49:52 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	updateevent(t_doom *doom)
{
	SDL_Keycode key;

	while (SDL_PollEvent(&doom->event))
	{
		doom->event.type == SDL_QUIT ? doom->win->state = 0 : 0;
		if (doom->event.type == SDL_KEYDOWN)
		{
			key = doom->event.key.keysym.sym;
			key == SDLK_ESCAPE ? doom->win->state = 0 : 0;
		}
	}
}
