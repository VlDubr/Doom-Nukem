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
	if (key == SDLK_UP)
		doom->player.rotate.x += -0.05;
	else if (key == SDLK_DOWN)
		doom->player.rotate.x += 0.05;
	else if (key == doom->input.moveleft)
		doom->player.rotate.y += -0.05;
	else
		doom->player.rotate.y += 0.05;
	printf("rotate: x%f y%f z%f\n", doom->player.rotate.x,
	doom->player.rotate.y, doom->player.rotate.z);
}

void	move(SDL_Keycode key, t_doom *doom, t_fvector new)
{
	printf("lookdir: x%f y%f z%f\n", new.x, new.y, new.z);

	doom->player.pos = (key == doom->input.moveforward) ? addfvtofv(doom->player.pos, new) : subfvtofv(doom->player.pos, new);

	printf("pos: x%f y%f z%f\n", doom->player.pos.x, doom->player.pos.y, doom->player.pos.z);
}

void	updateevent(t_doom *doom)
{
	t_fvector	forward;
	SDL_Keycode key;

	while (SDL_PollEvent(&doom->event))
	{
		doom->event.type == SDL_QUIT ? doom->win->state = 0 : 0;
		if (doom->event.type == SDL_KEYDOWN)
		{
			key = doom->event.key.keysym.sym;
			key == SDLK_ESCAPE ? doom->win->state = 0 : 0;

			forward = multfvector(doom->player.lookdir, 2, 2, 2);
			key == doom->input.moveforward || key == doom->input.movebackward ? move(key, doom, forward) : 0;

			key == doom->input.moveleft || key == doom->input.moveright ||
			key == SDLK_UP || key == SDLK_DOWN ? rotate(key, doom) : 0;

			if (key == SDLK_SPACE)
				playerjump(&doom->player);
			if (key == SDLK_p)
				printf("pos: x%f y%f z%f\nrotation: x%f y%f z%f\n", doom->player.pos.x, doom->player.pos.y, doom->player.pos.z,
				doom->player.rotate.x, doom->player.rotate.y, doom->player.rotate.z);
		}
	}
}
