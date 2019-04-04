/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createwindow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:11:50 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 13:47:24 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		destrotwindow(t_doom *doom)
{
	SDL_DestroyWindow(doom->win->window);
	SDL_DestroyRenderer(doom->win->renderer);
	ft_memdel((void**)&doom->win);
}

t_window	*createwindow(t_ivector2d size, char *title, Uint32 flag)
{
	t_window *result;

	if (!(result = (t_window*)malloc(sizeof(t_window))))
		error("Error: Memory is not allocated");
	result->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, size.x, size.y, flag);
	result->size = size;
	if (result->window == NULL)
		error("Error: Window not created");
	result->renderer = SDL_CreateRenderer(result->window, -1, 0);
	if (result->renderer == NULL)
		error("Error: Renderer not created");
	result->state = 1;
	return (result);
}
