/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:43:41 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/04 17:37:50 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_fvector2d		nextplayerposition(t_player player)
{
	t_fvector2d	new;

	new.x = sin(player.rotate.x);
	new.y = cos(player.rotate.y);
	return (new);
}
