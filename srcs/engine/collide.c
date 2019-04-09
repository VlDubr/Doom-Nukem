/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collide.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaniel <gdaniel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:40:19 by gdaniel           #+#    #+#             */
/*   Updated: 2019/04/09 18:58:19 by gdaniel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physic.h"


int	collideline(t_line line, t_fvector2d *crossing)
{
	t_fvector2d	cut1;
	t_fvector2d	cut2;
	t_fvector2d	prod1;
	t_fvector2d	prod2;

	cut1 = setfvector2d(line.a2.x - line.a1.x, line.a2.y - line.a1.y);
	cut2 = setfvector2d(line.b2.x - line.b1.x, line.b2.y - line.b1.y);

	prod1 = cross(cut1.x * (line.b1.x - line.a1.x), cut1.y * (line.b1.y - line.a1.y));
	prod1 = cross(cut2.x * (line.b2.x - line.a2.x), cut2.y * (line.b2.y - line.a2.y));

	if (SIGN(prod1.x) == SIGN(prod2.x))
		return (0);
	if (crossing)
	{
	}
}
