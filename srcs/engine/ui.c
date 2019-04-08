/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:48:34 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/08 17:56:53 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_button	setbutton(t_irect r, SDL_Surface *s, void (*clickevent)(void))
{
	t_button	b;

	b.rect = r;
	b.surf = s;
	b.clickevent = clickevent;
	return (b);
}

int			clickbutton(t_button button, t_mouse mouse)
{
	if (mouse.mousepos.x >= button.rect.start.x &&
	mouse.mousepos.x <= button.rect.start.x + button.rect.width &&
	mouse.mousepos.y >= button.rect.start.y &&
	mouse.mousepos.y <= button.rect.start.y + button.rect.height)
		button.clickevent();
}
