/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleartexture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:17:48 by gdaniel           #+#    #+#             */
/*   Updated: 2019/06/12 17:18:03 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	cleartexture(t_window *win)
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