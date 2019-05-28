/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawrect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 11:09:54 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/28 11:22:55 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawrect(t_doom *doom, t_irect rect, t_rgba color)
{
	t_ivector2d	cord;

	cord.y = rect.start.y;
	while (cord.y < rect.start.y + rect.height)
	{
		cord.x = rect.start.x;
		while (cord.x < rect.start.x + rect.width)
		{
			drawpoint(doom->win->pixels, doom->win->size, cord,
			color);
			cord.x++;
		}
		cord.y++;
	}
}