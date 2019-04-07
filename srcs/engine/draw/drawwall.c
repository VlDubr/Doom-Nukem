/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawwall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:29:39 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 18:36:33 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	drawwall(SDL_Renderer *r, t_fvector p1, t_fvector p2,
t_fvector p3, t_fvector p4)
{
	t_fvector2d cord;
	t_fvector2d	end;
	float		delta;
	int			i;

	cord.x = p1.x < 0 ? 0 : p1.x;
	delta = (p4.y - p3.y) / (p2.x - p1.x);
	i = 0;
	while (cord.x < p2.x)
	{
		cord.y = (p3.y + (delta * i)) < 0 ? 0 : p3.y + (delta * i);
		while (cord.y < p1.y + (delta * i))
		{
			SDL_RenderDrawPoint(r, cord.x, cord.y);
			cord.y++;
		}
		i++;
		cord.x++;
	}
}
