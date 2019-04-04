/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:41:37 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 19:04:05 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawsector(t_window *win, t_player player, size_t secid)
{

}

void	draw(t_doom *doom)
{
	size_t count;

	count = 0;
	SDL_RenderClear(doom->win->renderer);
	while (count < doom->thismap.sectorcount)
		drawsector(doom->win, doom->player, count);
	SDL_RenderPresent(doom->win->renderer);
}
