/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updateevent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:58 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 12:12:00 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	rotate(SDL_Keycode key, t_doom *doom)
{
	doom->player.rotate.z += key == doom->input.rotleft ? -0.05 : 0.05;
}

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
			key == doom->input.moveforward || key == doom->input.movebackward ? movefb(key, doom) : 0;
			key == doom->input.moveleft || key == doom->input.moveright ? movelr(key, doom) : 0;
			key == doom->input.rotleft || key == doom->input.rotright ? rotate(key, doom) : 0;
			key == doom->input.jump ? playerjump(&doom->player) : 0;
			printf("key: %d\n", key);
		}
	}
}
