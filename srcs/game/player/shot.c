/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:09:06 by gdaniel           #+#    #+#             */
/*   Updated: 2019/05/29 19:44:23 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	shot(Mix_Chunk *s, t_player p, t_input i, t_object **obj)
{
	if (i.mousekey[0])
	{
		if (p.targetid != 18446744073709551615u)
		{
			(*obj)[p.targetid].health -= 10;
		}
		Mix_PlayChannel(2, s, 0);
	}
}
