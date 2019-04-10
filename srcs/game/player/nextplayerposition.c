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

t_fvector2d	retnewpos(float rotz)
{
	t_fvector2d dir;

	dir.x = cos(rotz) * 5;
	dir.y = sin(rotz) * 5;
	return (dir);
}
